export module nhl:lottery_stats;

import temp_std;
import stdex;
import :lottery_teams;
import :lottery_round;
import :lottery_round_winners;

export namespace nhl::lottery
{
    struct lottery_stats
    {
        std::size_t simulations{ 1 };
        std::size_t rounds{ 2 };
        std::optional<lottery_teams> lottery_teams;

        // round -> { pre-lottery ranking -> # of wins }
        std::map<round_number, std::map<int, std::size_t>> lottery_winner_stats;

        // round winners (combination) -> # of wins for that combination
        // i.e. if 2 won the 1st round, and 7 the second, the combo is 2,7
        std::unordered_map<round_winners, std::size_t> round_winners_stats;

        // pre-lottery ranking -> { post-lottery ranking -> count }
        std::unordered_map<int, std::unordered_map<int, std::size_t>> draft_order_stats;

        // number of times original draft round was retained
        std::size_t original_draft_order_retained{ 0 };

        // round -> # of redraws in that round
        std::unordered_map<round_number, std::size_t> redraws;
    };

    void record_lottery_winner(lottery_stats& stats,
        round_number const& rn, int pre_lottery_ranking)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.lottery_winner_stats[rn][pre_lottery_ranking]++;
    }

    void record_lottery_winners(lottery_stats& stats,
        round_winners const& rw)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.round_winners_stats[rw]++;
    }

    void record_draft_order_ranking(lottery_stats& stats,
        int pre_lottery_ranking, int post_lottery_ranking)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.draft_order_stats[pre_lottery_ranking][post_lottery_ranking]++;
    }

    void record_original_draft_order_retained(lottery_stats& stats)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.original_draft_order_retained++;
    }

    // round -> # of redraws in that round
    void record_redraw(lottery_stats& stats, round_number const& rn)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.redraws[rn]++;
    }
}
