export module nhl:lottery_stats;

import temp_std;
import :lottery_teams;
import :lottery_round;

export namespace nhl::lottery
{
    struct lottery_stats
    {
        std::size_t simulations{ 1 };
        std::size_t rounds{ 2 };
        std::optional<lottery_teams> lottery_teams;

        // round -> { pre-lottery ranking -> # of wins }
        std::map<round_number, std::map<int, std::size_t>> lottery_winner_stats;

        // pre-lottery ranking -> { post-lottery ranking -> count }
        std::unordered_map<int, std::unordered_map<int, std::size_t>> draft_order_stats;

        // number of times original draft round was retained
        std::size_t original_draft_order_retained{ 0 };

        // round -> # of redraws in that round
        std::unordered_map<round_number, std::size_t> redraws;
    };
}
