add_library(nhl STATIC
    #MODULE
        lottery/ball.ixx
        lottery/combination.ixx
        lottery/combination_table.ixx
        lottery/combination_value.ixx
        lottery/lottery_print.ixx
        lottery/lottery_team.ixx
        lottery/lottery_teams.ixx
        lottery/lottery.ixx
        lottery/machine.ixx
        lottery/odds.ixx
        lottery/parameters.ixx
        lottery/potential_winners.ixx
        lottery/ranking.ixx
        lottery/ranking_combinations.ixx
        lottery/round.ixx
        lottery/round_winners.ixx
        lottery/stats.ixx

        math/cmath.ixx
        math/percentage.ixx

        stdex/functional.ixx
        stdex/stdex.ixx
        stdex/type_traits.ixx

        conference.ixx
        division.ixx
        game.ixx
        league.ixx
        nhl.ixx
        schedule.ixx
        standings.ixx
        temp_std.ixx
        team_record.ixx
        team.ixx
        text_literals.ixx
)

target_compile_features(nhl PUBLIC cxx_std_23)
