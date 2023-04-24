export module nhl:standings;

import temp_std;
import :team;
import :team_record;

export namespace nhl
{
    using enum team_id;

    struct standings
    {
        std::array<team_record, 32> teams =
        {
            team_record{ bos, 77, 60, 12, 5, 50, 56, 4, 3, 286, 166 },
            team_record{ car, 77, 50, 18, 9, 37, 46, 4, 3, 251, 198 },
            team_record{ njd, 78, 49, 21, 8, 37, 47, 2, 4, 271, 217 },
            team_record{ vgk, 78, 48, 22, 8, 35, 43, 5, 3, 259, 223 },
            team_record{ tor, 77, 46, 21, 10, 39, 45, 1, 2, 262, 213 },
            team_record{ nyr, 77, 45, 21, 11, 35, 41, 4, 2, 261, 207 },
            team_record{ edm, 78, 46, 23, 9, 42, 46, 0, 4, 309, 255 },
            team_record{ lak, 78, 45, 23, 10, 35, 39, 6, 3, 267, 245 },
            team_record{ col, 76, 46, 24, 6, 32, 40, 6, 3, 256, 210 },
            team_record{ dal, 77, 42, 21, 14, 35, 39, 3, 3, 267, 213 },
            team_record{ min, 77, 44, 23, 10, 32, 37, 7, 6, 232, 209 },
            team_record{ tbl, 77, 45, 26, 6, 37, 42, 3, 2, 267, 231 },
            team_record{ sea, 77, 43, 26, 8, 34, 43, 0, 4, 272, 243 },
            team_record{ wpg, 77, 43, 31, 3, 33, 42, 1, 1, 233, 215 },
            team_record{ fla, 78, 40, 31, 7, 34, 38, 2, 1, 274, 261 },
            team_record{ nyi, 78, 39, 30, 9, 33, 38, 1, 5, 227, 214 },
            team_record{ cgy, 78, 36, 27, 15, 29, 34, 2, 3, 250, 244 },
            team_record{ nsh, 77, 39, 30, 8, 28, 34, 5, 2, 216, 227 },
            team_record{ pit, 78, 38, 30, 10, 29, 37, 1, 1, 249, 254 },
            team_record{ buf, 76, 37, 32, 7, 28, 36, 1, 3, 271, 278 },
            team_record{ ott, 78, 37, 34, 7, 29, 35, 2, 1, 246, 254 },
            team_record{ det, 77, 35, 33, 9, 28, 32, 3, 3, 231, 252 },
            team_record{ stl, 78, 36, 35, 7, 27, 33, 3, 3, 255, 288 },
            team_record{ wsh, 77, 34, 34, 9, 26, 32, 2, 4, 240, 243 },
            team_record{ van, 77, 34, 36, 7, 22, 29, 5, 2, 262, 287 },
            team_record{ phi, 77, 29, 35, 13, 26, 27, 2, 1, 209, 257 },
            team_record{ ari, 78, 27, 38, 13, 20, 24, 3, 4, 216, 282 },
            team_record{ mtl, 78, 30, 42, 6, 20, 25, 5, 2, 219, 289 },
            team_record{ sjs, 77, 22, 39, 16, 16, 21, 1, 6, 226, 295 },
            team_record{ chi, 77, 25, 46, 6, 17, 23, 2, 2, 190, 280 },
            team_record{ cbj, 77, 24, 45, 8, 15, 23, 1, 1, 205, 307 },
            team_record{ ana, 77, 23, 44, 10, 13, 20, 3, 3, 195, 317 }
        };
    };
}

/*
inline constexpr std::array standings
{
    team_record{ BOS, 77, 60, 12, 5, 50, 56, 4, 3, 286, 166 },
    team_record{ CAR, 77, 50, 18, 9, 37, 46, 4, 3, 251, 198 },
    team_record{ NJD, 78, 49, 21, 8, 37, 47, 2, 4, 271, 217 },
    team_record{ VGK, 78, 48, 22, 8, 35, 43, 5, 3, 259, 223 },
    team_record{ TOR, 77, 46, 21, 10, 39, 45, 1, 2, 262, 213 },
    team_record{ NYR, 77, 45, 21, 11, 35, 41, 4, 2, 261, 207 },
    team_record{ EDM, 78, 46, 23, 9, 42, 46, 0, 4, 309, 255 },
    team_record{ LAK, 78, 45, 23, 10, 35, 39, 6, 3, 267, 245 },
    team_record{ COL, 76, 46, 24, 6, 32, 40, 6, 3, 256, 210 },
    team_record{ DAL, 77, 42, 21, 14, 35, 39, 3, 3, 267, 213 },
    team_record{ MIN, 77, 44, 23, 10, 32, 37, 7, 6, 232, 209 },
    team_record{ TBL, 77, 45, 26, 6, 37, 42, 3, 2, 267, 231 },
    team_record{ SEA, 77, 43, 26, 8, 34, 43, 0, 4, 272, 243 },
    team_record{ WPG, 77, 43, 31, 3, 33, 42, 1, 1, 233, 215 },
    team_record{ FLA, 78, 40, 31, 7, 34, 38, 2, 1, 274, 261 },
    team_record{ NYI, 78, 39, 30, 9, 33, 38, 1, 5, 227, 214 },
    team_record{ CGY, 78, 36, 27, 15, 29, 34, 2, 3, 250, 244 },
    team_record{ NSH, 77, 39, 30, 8, 28, 34, 5, 2, 216, 227 },
    team_record{ PIT, 78, 38, 30, 10, 29, 37, 1, 1, 249, 254 },
    team_record{ BUF, 76, 37, 32, 7, 28, 36, 1, 3, 271, 278 },
    team_record{ OTT, 78, 37, 34, 7, 29, 35, 2, 1, 246, 254 },
    team_record{ DET, 77, 35, 33, 9, 28, 32, 3, 3, 231, 252 },
    team_record{ STL, 78, 36, 35, 7, 27, 33, 3, 3, 255, 288 },
    team_record{ WSH, 77, 34, 34, 9, 26, 32, 2, 4, 240, 243 },
    team_record{ VAN, 77, 34, 36, 7, 22, 29, 5, 2, 262, 287 },
    team_record{ PHI, 77, 29, 35, 13, 26, 27, 2, 1, 209, 257 },
    team_record{ ARI, 78, 27, 38, 13, 20, 24, 3, 4, 216, 282 },
    team_record{ MTL, 78, 30, 42, 6, 20, 25, 5, 2, 219, 289 },
    team_record{ SJS, 77, 22, 39, 16, 16, 21, 1, 6, 226, 295 },
    team_record{ CHI, 77, 25, 46, 6, 17, 23, 2, 2, 190, 280 },
    team_record{ CBJ, 77, 24, 45, 8, 15, 23, 1, 1, 205, 307 },
    team_record{ ANA, 77, 23, 44, 10, 13, 20, 3, 3, 195, 317 }
};
*/
