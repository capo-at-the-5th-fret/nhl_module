export module nhl:lottery_potential_winners;

import temp_std;
import :lottery_ball;

export namespace nhl::lottery
{
    struct potential_winners
    {
        std::map<ball, int> data;

        std::set<int> unique_winners() const
        {
            return data | std::views::values |
                std::ranges::to<std::set>();
        }
    };

    inline bool is_clean_sweep(potential_winners const& pw)
    {
        bool ret{ false };

        std::set<int> winner_set;
        for (auto const& [ball, team] : pw.data)
        {
            winner_set.insert(team);
        }

        return winner_set.size() == 1;
    }

    inline bool is_royal_flush(potential_winners const& pw)
    {
        bool ret{ false };

        std::set<int> winner_set;
        for (auto const& [ball, team] : pw.data)
        {
            winner_set.insert(team);
        }

        return (winner_set.size() == 11) &&
            (*winner_set.begin() == 1) &&
            (*winner_set.rbegin() == 11);
    }

    inline bool is_flush(potential_winners const& pw)
    {
        bool ret{ false };

        std::set<int> winner_set;
        for (auto const& [ball, team] : pw.data)
        {
            winner_set.insert(team);
        }

        return winner_set.size() == 11;
    }
}
