export module nhl:league;

import temp_std;
import :conference;

export namespace nhl
{
    inline constexpr std::size_t team_count{ 32 };

    struct league
    {
        std::array<conference_id, 2> conferences;
    };

    inline constexpr league nhl
    {
        { conference_id::east, conference_id::west }
    };
}

