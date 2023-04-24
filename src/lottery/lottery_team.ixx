export module nhl:lottery_team;

import :team;

export namespace nhl::lottery
{
    struct team
    {
        int ranking;
        nhl::team_id team_id;
    };
}
