export module nhl:game;

import :team;

export namespace nhl
{
    struct game
    {
        team_id visitor;
        team_id home;
    };
}
