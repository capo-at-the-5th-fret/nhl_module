export module nhl:lottery_print;

import temp_std;
import math;
import :lottery_parameters;
import :lottery_ranking;
import :lottery_stats;

export namespace nhl::lottery
{
    inline void print_lottery_winner_stats(lottery_stats const& stats)
    {
        for (const auto& [round, round_stats] : stats.lottery_winner_stats)
        {
            const std::string_view simulation_suffix =
                (stats.simulations == 1) ? "simulation" : "simulations";

            temp::println("[ Round {} Lottery Winners ] ({} {})", round,
                stats.simulations, simulation_suffix);
            temp::println("");

            temp::println("{:^10} {:^10} {:^10}", "Team", "Wins", "Pct.");
            temp::println("{0:10} {0:10} {0:10}", "----------");

            for (auto const& ranking : rankings)
            {
                std::size_t count{ 0 };

                if (auto pos = round_stats.find(ranking);
                    pos != round_stats.end())
                {
                    count = pos->second;
                }

                temp::println("{:^10} {:^10} {:^10.3f}", ranking,
                    count,
                    math::percent(count, stats.simulations).to_ratio()
                );
            }

            temp::println("{}", "--------------------------------");

            std::size_t redraws{ 0 };

            if (auto pos = stats.redraws.find(round);
                pos != stats.redraws.end())
            {
                redraws = pos->second;
            }

            temp::println("{:^10} {:^10} {:^10.3f}", "Redraws", redraws,
                math::percent(redraws, stats.simulations).to_ratio());
            temp::println("");

            temp::println("{:^17} {:^10} {:^10}", "Potential Winners", "Count", "Pct.");
            temp::println("{0:17} {1:10} {1:10}", "-----------------", "----------");

            {
                for (auto [potential_winners, count] : stats.potential_winners)
                {
                    temp::println("{:^17} {:^10} {:^10.6f}", potential_winners,
                        count, math::percent(count, stats.simulations).to_ratio());
                }
            }

            temp::println("{}", "---------------------------------------");

            {
                std::size_t clean_sweeps{ 0 };

                if (auto pos = stats.clean_sweeps.find(round);
                    pos != stats.clean_sweeps.end())
                {
                    clean_sweeps = pos->second;
                }

                if (clean_sweeps > 0)
                {
                    temp::println("{:^17} {:^10} {:^10.6f}", "Clean Sweeps",
                        clean_sweeps,
                        math::percent(clean_sweeps, stats.simulations).to_ratio());
                }
            }

            {
                std::size_t royal_flushes{ 0 };

                if (auto pos = stats.royal_flushes.find(round);
                    pos != stats.royal_flushes.end())
                {
                    royal_flushes = pos->second;
                }

                if (royal_flushes > 0)
                {
                    temp::println("{:^17} {:^10} {:^10.6f}", "Royal Flushes",
                        royal_flushes,
                        math::percent(royal_flushes, stats.simulations).to_ratio());
                }
            }

            {
                std::size_t flushes{ 0 };

                if (auto pos = stats.flushes.find(round);
                    pos != stats.flushes.end())
                {
                    flushes = pos->second;
                }

                if (flushes > 0)
                {
                    temp::println("{:^17} {:^10} {:^10.6f}", "Flushes",
                        flushes,
                        math::percent(flushes, stats.simulations).to_ratio());
                }
            }

            temp::println("");
        }
    }

    inline void print_lottery_round_winners_stats(lottery_stats const& stats)
    {
        const std::string_view simulation_suffix =
                (stats.simulations == 1) ? "simulation" : "simulations";

        temp::println("[ Lottery Round Winners ] ({} {})",
            stats.simulations, simulation_suffix);
        temp::println("");

        temp::println("{:^10} {:^12} {:^10} {:^10}",
            "#", "Winners", "Occurances", "Pct.");
        temp::println("{0:10} {1:12} {0:10} {0:10}", "----------", "------------");

        // sort the combinations with the help of a vector + reference_wrapper

        using kv_type = std::add_const_t<
            typename decltype(stats.round_winners_stats)::value_type>;

        std::vector<std::reference_wrapper<kv_type>> sorted_round_winners
            ( stats.round_winners_stats.begin(), stats.round_winners_stats.end() );

        std::ranges::sort(sorted_round_winners,
            [](auto const& lhs, auto const& rhs)
            {
                //return lhs.get().first < rhs.get().first;
                return rhs.get().second < lhs.get().second;
            });

        for (int i = 1; auto const& round_winner : sorted_round_winners)
        {
            temp::println("{:^10} {:^12} {:^10} {:^10.6f}",
                i++,
                round_winner.get().first,
                round_winner.get().second,
                math::percent(round_winner.get().second,
                stats.simulations).to_ratio()
            );
        }

        temp::println("");
    }

    inline void print_draft_order_lottery_stats(lottery_stats const& stats)
    {
        const std::string_view simulation_suffix =
            (stats.simulations == 1) ? "simulation" : "simulations";

        temp::println("[ Draft Order Statistics ] ({} {})", stats.simulations,
            simulation_suffix);
        temp::println("");

        temp::println("Original draft order retained: {:.1f}%",
            math::percent(stats.original_draft_order_retained,
                stats.simulations));
        temp::println("");

        constexpr std::string_view header_format =
        {
            "{:^5} {:^5} {:^5} {:^5} {:^5} {:^5} {:^5} {:^5} "
            "{:^5} {:^5} {:^5} {:^5} {:^5} {:^5} {:^5} {:^5} "
            "{:^5}"
        };

        const auto header = std::format(header_format, "Team",
            "1", "2", "3", "4", "5", "6", "7", "8",
            "9", "10", "11", "12", "13", "14", "15", "16"
        );

        temp::println("{}", header);

        const std::string header_underline(header.size(), '-');
        temp::println("{}", header_underline);

        // team ranking is the pre-lottery ranking
        for (auto const& team_ranking : nhl::lottery::rankings)
        {
            temp::print("{:^5} ", team_ranking);

            // col is the post-lottery ranking
            for (int col = 1; col <= 16; ++col)
            {
                std::size_t count = 0;

                // .first - pre-lottery ranking
                // .second - map of post-lottery rankings for the team
                if (const auto ranking_stats =
                    stats.draft_order_stats.find(team_ranking); ranking_stats !=
                    stats.draft_order_stats.end())
                {
                    if (auto pos = ranking_stats->second.find(col);
                        pos != ranking_stats->second.end())
                    {
                        count = pos->second;
                    }
                }

                if (count == 0)
                {
                    temp::print("{:^5}", "-");
                }
                else
                {
                    temp::print("{:^5.3f}", math::percent(count,
                        stats.simulations).to_ratio());
                }

                if (col < 16)
                {
                    temp::print(" ");
                }
            }

            temp::println("");
        }
    }

    inline void print_draft_order(std::array<int, nhl::lottery::rankings_count>
        const& draft_order)
    {
        temp::println("[ Draft Order ]");
        temp::println("");

        temp::println("{:^3} {:^4} {:^3}", " # ", "Team", "+/-");
        temp::println("{:^3} {:^4} {:^3}", "---", "----", "---");

        for (int ranking = 1; auto team : draft_order)
        {
            const auto change = [&ranking, &team]() -> std::string
            {
                if (const int change = team - ranking; change != 0)
                {
                    return std::format("{:+}", change);
                }
                else
                {
                    return "-";
                }
            }();

            temp::println("{:^3} {:^4} {:^3}", ranking, team, change);

            ++ranking;
        }

        temp::println("");
    }
}
