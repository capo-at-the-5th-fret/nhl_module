export module nhl:lottery_combination_table;

import temp_std;
import :lottery_parameters;
import :lottery_ranking_combinations;
import :lottery_combination_value;

export namespace nhl::lottery
{
    class combination_table
    {
    public:
        using combinations_type = std::unordered_map<combination_value,
            std::size_t>;
        using ranking_combination_distribution_type = std::array<int,
            combinations_used_count>;

        combination_table(bool randomize = true) :
            ranking_combination_distribution_{
                ranking_combination_distribution(randomize) }
        {
        }

        void randomize()
        {
            static std::random_device rd;
            static std::mt19937 gen{ rd() };

            // randomize the distribution array (the combo map is constant)
            std::ranges::shuffle(ranking_combination_distribution_, gen);
        }

        static combinations_type const& combinations()
        {
            // combinations are shared data that never changes
            static combinations_type combinations = []()
            {
                combinations_type ret;

                // map combo -> distribution_index
                std::size_t dist_index{ 0 };
                nhl::lottery::for_each_combination_value(
                    [&](auto const& combo)
                {
                    if (dist_index < combinations_used_count)
                    {
                        ret[combo] = dist_index++;
                    }
                    // left overs are considered redraws. If there's a need for
                    // something more advanced, pass a predicate into the function
                    // that returns whether a combo is a redraw
                    // 
                    // else
                    // {
                    //     combinations_[combo] = 0;
                    // }
                });

                return ret;
            }();

            return combinations;
        }

        std::optional<int> lookup(combination_value const& combo) const
        {
            if (auto pos = combinations().find(combo);
                pos != combinations().end())
            {
                return ranking_combination_distribution_[pos->second];
            }

            return std::nullopt;
        }

    private:
        ranking_combination_distribution_type ranking_combination_distribution_;
    };

    inline void print_combination_table(combination_table const& table)
    {
        temp::println("Combination Table");
        temp::println("-----------------");

        // sort the combinations with the help of a vector + reference_wrapper

        using kv_type = std::add_const_t<
            typename combination_table::combinations_type::value_type>;

        std::vector<std::reference_wrapper<kv_type>> sorted_combinations
            ( table.combinations().begin(), table.combinations().end() );

        std::ranges::sort(sorted_combinations,
            [](auto const& lhs, auto const& rhs)
            {
                return lhs.get().first < rhs.get().first;
            });

        for (auto const& combo : sorted_combinations)
        {
            std::cout << combo.get().first << " => " << combo.get().second <<
                "\n";
        }

        temp::println("");
    }
}
