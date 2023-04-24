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

            std::size_t redraws{ 0 };

            if (auto pos = stats.redraws.find(round);
                pos != stats.redraws.end())
            {
                redraws = pos->second;
            }

            temp::println("{} redraws", redraws);
            temp::println("");
        }
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
