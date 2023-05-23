#include <cassert>

import temp_std;
import nhl;

// NOTE: This include must come after the imports, otherwise errors
#include <cxxopts.hpp>

inline constexpr std::string_view app_name{ "nhl_dls" };
inline constexpr std::string_view app_version{ "1.0" };

struct app_options
{
    std::optional<std::size_t> simulations;
    std::optional<std::size_t> rounds;

    static constexpr std::size_t min_simulations() { return 1; }

    template <std::integral T>
    static constexpr bool is_valid_simulations(T simulations)
    {
        return std::cmp_less_equal(min_simulations(), simulations);
    }

    static constexpr std::size_t min_rounds() { return 1; }
    static constexpr std::size_t max_rounds() { return 3; }

    template <std::integral T>
    static constexpr bool is_valid_rounds(T rounds)
    {
        return std::cmp_less_equal(min_rounds(), rounds) &&
            std::cmp_less_equal(rounds, max_rounds());
    }

    static constexpr std::size_t default_simulations{ 1 };
    static constexpr std::size_t default_rounds{ 2 };
};

int main(int argc, char* argv[])
{
    app_options options;

    cxxopts::Options cli_options(std::string{ app_name });
    cli_options.custom_help("[options]");

    try
    {
        cli_options.add_options()
            ("s,simulations", "The number of simulations to run",
                cxxopts::value<std::size_t>())
            ("r,rounds", "The number of lottery rounds per simulation",
                cxxopts::value<std::size_t>())
            ("v,version", "Print the version number and exit")
            ("h,help", "Print the usage information and exit")
        ;

        auto result = cli_options.parse(argc, argv);

        if (result.count("help"))
        {
            temp::println("{}", cli_options.help());
            std::exit(0);
        }
        else if (result.count("version"))
        {
            temp::println("{} version {}", app_name, app_version);
            std::exit(0);
        }

        if (result.count("simulations"))
        {
            if (auto s = result["simulations"].as<std::size_t>();
                app_options::is_valid_simulations(s))
            {
                options.simulations = s;
            }
            else
            {
                throw std::out_of_range("Invalid value for simulations");
            }
        }

        if (result.count("rounds"))
        {
            if (auto r = result["rounds"].as<std::size_t>();
                app_options::is_valid_rounds(r))
            {
                options.rounds = r;
            }
            else
            {
                throw std::out_of_range("Invalid value for rounds");
            }
        }
    }
    catch (std::exception const& e)
    {
        temp::println("Command line error: {}", e.what());
        temp::println("{}", cli_options.help());
        std::exit(1);
    }

    // if at least one cli arg was used, set the defaults so it can run without
    // user interaction
    if (options.simulations && !options.rounds)
    {
        options.rounds = app_options::default_rounds;
    }
    else if (options.rounds && !options.simulations)
    {
        options.simulations = app_options::default_simulations;
    }

    while (!options.simulations)
    {
        std::string input;
        temp::println("Enter the number of simulations to run (>= {}; default = {})",
            app_options::min_simulations(), app_options::default_simulations);
        temp::println("- or -");
        temp::println("'q' to quit");

        std::getline(std::cin, input);

        if (input == "q")
        {
            return 0;
        }
        else if (input.empty())
        {
            options.simulations = app_options::default_simulations;
        }
        else
        {
            try
            {
                if (const auto s = std::stoll(input);
                    app_options::is_valid_simulations(s))
                {
                    options.simulations = static_cast<std::size_t>(s);
                }
            }
            catch (std::exception const&)
            {
            }
        }
    }

    while (!options.rounds)
    {
        std::string input;
        temp::println("Enter the number of lottery rounds (>= {} and <= {}; default = {})",
            app_options::min_rounds(), app_options::max_rounds(),
            app_options::default_rounds);
        temp::println("- or -");
        temp::println("'q' to quit");

        std::getline(std::cin, input);

        if (input == "q")
        {
            return 0;
        }
        else if (input.empty())
        {
            options.rounds = app_options::default_rounds;
        }
        else
        {
            try
            {
                if (const auto r = std::stoll(input);
                    app_options::is_valid_rounds(r))
                {
                    options.rounds = static_cast<std::size_t>(r);
                }
            }
            catch (std::exception const&)
            {
            }
        }
    }

    // Change the following variables
    const bool print_progress{ false };
    const bool print_individual_drawn_balls{ true };

    nhl::lottery::lottery_stats stats
    {
        .simulations = static_cast<std::size_t>(*options.simulations),
        .rounds = static_cast<std::size_t>(*options.rounds)
    };

    stats.lottery_teams = nhl::lottery::lottery_teams
    {
        // 2023 final standings
        std::array
        {
            nhl::lottery::team{ 1, nhl::team_id::ana },
            nhl::lottery::team{ 2, nhl::team_id::cbj },
            nhl::lottery::team{ 3, nhl::team_id::chi },
            nhl::lottery::team{ 4, nhl::team_id::sjs },
            nhl::lottery::team{ 5, nhl::team_id::mtl },
            nhl::lottery::team{ 6, nhl::team_id::ari },
            nhl::lottery::team{ 7, nhl::team_id::phi },
            nhl::lottery::team{ 8, nhl::team_id::wsh },
            nhl::lottery::team{ 9, nhl::team_id::det },
            nhl::lottery::team{ 10, nhl::team_id::stl },
            nhl::lottery::team{ 11, nhl::team_id::van },
            nhl::lottery::team{ 12, nhl::team_id::ott },
            nhl::lottery::team{ 13, nhl::team_id::buf },
            nhl::lottery::team{ 14, nhl::team_id::pit },
            nhl::lottery::team{ 15, nhl::team_id::nsh },
            nhl::lottery::team{ 16, nhl::team_id::cgy }
        }
    };

    temp::println("Running simulation(s)...");
    temp::println("");

    // TODO: For fast times, uncomment this and comment out the table inside the
    // for_each loop below. Doing this will randomize once, and that table will
    // be used for all simulations
    //nhl::lottery::combination_table combinations{ true };

    const auto start = std::chrono::high_resolution_clock::now();

    const auto vw = std::views::iota(std::size_t{ 0 }, stats.simulations);
    std::for_each(std::execution::par, vw.begin(), vw.end(),
        [&stats](auto sim)
    {
        if (print_progress)
        {
            temp::println("[ NHL Lottery Draft - Simulation {} of {} ]",
                sim + 1, stats.simulations);
            temp::println("");
        }

        nhl::lottery::machine machine;
        nhl::lottery::combination_table combinations{ true };

        auto tentative_draft_order{ nhl::lottery::rankings };
        decltype(tentative_draft_order) final_draft_order{};

        nhl::lottery::round_winners round_winners;

        for (nhl::lottery::round_number round{ 1 }; round <=
            nhl::lottery::round_number{ static_cast<int>(stats.rounds) };)
        {
            if (print_progress)
            {
                temp::println("Running the machine for round {} of {}",
                    round, stats.rounds);
            }
        
            machine.load_balls(std::span{ nhl::lottery::balls });

            std::array<nhl::lottery::ball,
                nhl::lottery::balls_to_draw> drawn_balls;

            for (std::size_t b = 0; b < nhl::lottery::balls_to_draw; ++b)
            {
                if (print_progress && print_individual_drawn_balls)
                {
                    temp::print("    drawing ball {} ", b + 1);

                    for (int k = 0; k < 10; ++k)
                    {
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(150));
                        temp::print("-");
                    }
                    temp::print("> ");
                }

                const auto ball = machine.draw_ball();
                drawn_balls[b] = ball;

                if (print_progress && print_individual_drawn_balls)
                {
                    temp::println("{}", ball);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                if (round == nhl::lottery::round_number{ 1 } &&
                    (b == (nhl::lottery::balls_to_draw - 2)))
                {
                    std::set<nhl::lottery::ball> balls
                    {
                        drawn_balls.begin(),
                        std::next(drawn_balls.begin(), b + 1)
                    };

                    {
                        const auto pw = nhl::lottery::get_potential_winners(
                            combinations, balls);

                        record_potential_winners(stats, round, pw);

                        if (nhl::lottery::is_clean_sweep(pw))
                        {
                            record_clean_sweep(stats, round);
                        }
                        else if (nhl::lottery::is_royal_flush(pw))
                        {
                            record_royal_flush(stats, round);
                        }
                        else if (nhl::lottery::is_flush(pw))
                        {
                            record_flush(stats, round);
                        }
                    }
                }
            }

            nhl::lottery::combination combo{ drawn_balls };

            if (const auto winner = combinations.lookup(to_value(combo)))
            {
                if (print_progress)
                {
                    temp::println("The combination {} belongs to team {}.",
                        combo, *winner);
                }

                const auto winner_index = *winner - 1;

                // winner was found in the final draft order list; this means
                // the winner is already locked in from a previous round and a
                // redraw is required
                if (auto pos = std::ranges::find(final_draft_order, winner);
                    pos != std::ranges::end(final_draft_order))
                {
                    record_redraw(stats, round);

                    if (print_progress)
                    {
                        temp::println(
                            "{} is already locked in to the {} pick. A redraw is required",
                            *winner, std::distance(final_draft_order.begin(), pos) + 1);
                    }
                    continue;
                }

                // find the first 'empty' slot in the final draft order list
                auto slot_pos = std::ranges::find(final_draft_order, 0);
                assert(slot_pos != std::ranges::end(final_draft_order));

                // the slot up for grabs this round
                const auto slot = slot_pos -
                    std::ranges::begin(final_draft_order) + 1;

                // team that won can jump to slot
                if (winner <= (slot + nhl::lottery::max_ranking_jump))
                {
                    *slot_pos = *winner;
                    tentative_draft_order[winner_index] = 0;
                }
                // team that won can't jump to slot
                else
                {
                    // highest ranked team remaining in the pre-lottery draft order
                    // 'wins' the slot
                    auto surrogate_winner_pos = std::ranges::find_if_not(
                        tentative_draft_order, [](auto t) { return t == 0; });
                    assert(surrogate_winner_pos !=
                        std::ranges::end(tentative_draft_order));

                    *slot_pos = *surrogate_winner_pos;
                    *surrogate_winner_pos = 0;

                    // The slot that the winner will move to
                    const auto jump_slot = *winner -
                        nhl::lottery::max_ranking_jump;

                    auto jump_slot_pos = std::ranges::find(
                        std::ranges::begin(final_draft_order) + (jump_slot - 1),
                        std::ranges::end(final_draft_order), 0);
                    assert(jump_slot_pos != std::ranges::end(final_draft_order));

                    *jump_slot_pos = *winner;
                    tentative_draft_order[winner_index] = 0;
                }

                if (print_progress)
                {
                    temp::println("");
                }

                record_lottery_winner(stats, round, *winner);
                round_winners.push(*winner);
                ++round;
            }
            else
            {
                record_redraw(stats, round);

                if (print_progress)
                {
                    temp::println("The combination {} requires a redraw.",
                        combo);
                }
            }

            if (print_progress)
            {
                temp::println("");
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }

        // add remaining teams to final_draft_order, in order from 1 to 16
        auto empty_slots = final_draft_order |
            std::views::filter([](auto t) { return t == 0; });
        auto remaining_seeds = tentative_draft_order |
            std::views::filter([](auto t) { return t != 0; });

        for (auto pos = empty_slots.begin(); const auto team : remaining_seeds)
        {
            assert(pos != std::ranges::end(empty_slots));
            *pos = team;
            ++pos;
        }

        record_lottery_winners(stats, round_winners);

        for (int ranking = 1; auto team : final_draft_order)
        {
            record_draft_order_ranking(stats, team, ranking);
            ++ranking;
        }

        if (std::ranges::is_sorted(final_draft_order))
        {
            record_original_draft_order_retained(stats);
        }

        if (print_progress)
        {
            nhl::lottery::print_draft_order(final_draft_order);
        }
    });

    const auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    temp::println("The simulation(s) took {} seconds to complete", diff.count());
    temp::println("");

    nhl::lottery::print_lottery_winner_stats(stats);
    nhl::lottery::print_lottery_round_winners_stats(stats);
    nhl::lottery::print_draft_order_lottery_stats(stats);
}
