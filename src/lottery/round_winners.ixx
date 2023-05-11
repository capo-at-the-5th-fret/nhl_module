export module nhl:lottery_round_winners;

import temp_std;
import stdex;
import :lottery_round;

export namespace nhl::lottery
{
    class round_winners
    {
    public:
        using winners_type = std::vector<int>;

        using iterator = winners_type::iterator;
        using const_iterator = winners_type::const_iterator;

        auto operator<=>(round_winners const&) const = default;

        void push(int winner)
        {
            winners_.push_back(winner);
        }

        std::size_t size() const
        {
            return winners_.size();
        }

        winners_type const& winners() const { return winners_; }

        iterator begin() { return winners_.begin(); }
        iterator end() { return winners_.end(); }

        const_iterator begin() const { return winners_.begin(); }
        const_iterator end() const { return winners_.end(); }

    private:
        winners_type winners_;
    };
}

#if 0
// TODO: Replace with ranges formatting in C++23
// Reference:
// https://www.modernescpp.com/index.php/extend-std-format-in-c-20-for-user-defined-types
template <>
struct std::formatter<nhl::lottery::round_winners>
{
    std::string value_format;

    constexpr auto parse(format_parse_context& ctx)
    {
        value_format= "{:";
        for (auto it= begin(ctx); it != end(ctx); ++it)
        {
            value_format += *it;

            if (*it == '}')
                return it;
        }

        return end(ctx);
    }

    auto format(nhl::lottery::round_winners const& rw, std::format_context& ctx)
    {
        auto&& out= ctx.out();

        std::format_to(out, "[");

        if (rw.size() > 0)
        {
            std::vformat_to(out, value_format,
                std::make_format_args(rw.winners()[0]));
        }

        for (std::size_t i= 1; i < rw.size(); ++i)
        {
            std::vformat_to(out, ", " + value_format,
                std::make_format_args(rw.winners()[i]));
        }

        return std::format_to(out, "]");
    }
};
#endif

// TODO: Replace with ranges formatting in C++23
template <>
struct std::formatter<nhl::lottery::round_winners> : std::formatter<string>
{
    auto format(nhl::lottery::round_winners const& rw,
        format_context& ctx) const
    {
        std::string text;

        if (rw.size() == 1)
        {
            text = std::format("{}", rw.winners()[0]);
        }
        else if (rw.size() == 2)
        {
            text = std::format("[{}, {}]", rw.winners()[0], rw.winners()[1]);
        }
        else if (rw.size() == 3)
        {
            text = std::format("[{}, {}, {}]", rw.winners()[0],
                rw.winners()[1], rw.winners()[2]);
        }

        return formatter<string>::format(text, ctx);
    }
};

export template<>
struct std::hash<nhl::lottery::round_winners>
{
    std::size_t operator()(nhl::lottery::round_winners const& key) const noexcept
    {
        std::size_t ret{ 0 };
        for (const auto winner : key)
        {
            stdex::hash_combine(ret, winner);
        }
        return ret;
    }
};
