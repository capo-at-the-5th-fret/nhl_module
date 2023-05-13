export module nhl:lottery_stats;

import temp_std;
import stdex;
import :lottery_teams;
import :lottery_round;
import :lottery_round_winners;
import :lottery_potential_winners;

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

        // Number of potential winners after 3 balls are drawn -> count
        std::unordered_map<std::size_t, std::size_t> potential_winners;

        // 'clean sweep' is when a single team is guaranteed to win a lottery
        // with the final ball (one team has all 11 combos that can win)
        std::unordered_map<round_number, std::size_t> clean_sweeps;

        // 'royal flush' is when each team from 1 to 11 in the first round has
        // a chance to win a lottery with the final ball
        std::unordered_map<round_number, std::size_t> royal_flushes;

        // 'flush' is when 11 teams have a chance to win a lottery with the
        // final ball
        std::unordered_map<round_number, std::size_t> flushes;
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

    void record_potential_winners(lottery_stats& stats, round_number const& rn,
        potential_winners const& pw)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.potential_winners[pw.unique_winners().size()]++;
    }

    void record_clean_sweep(lottery_stats& stats, round_number const& rn)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.clean_sweeps[rn]++;
    }

    void record_royal_flush(lottery_stats& stats, round_number const& rn)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.royal_flushes[rn]++;
    }

    void record_flush(lottery_stats& stats, round_number const& rn)
    {
        static std::mutex m;
        std::unique_lock lk{ m };
        stats.flushes[rn]++;
    }
}
