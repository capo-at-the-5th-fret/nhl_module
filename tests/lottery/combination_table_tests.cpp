#include <doctest/doctest.h>

import nhl;

TEST_CASE("combination_table")
{
    using nhl::lottery::combination_table;

    combination_table ct;
    ct.populate();

    //nhl::lottery::print_combination_table(ct);
}
