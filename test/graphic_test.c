#include <liblive/graphic.h>

#include <ctest.h>

CTEST(GRAPHIC_TEST, get_live_count)
{
    Grid test_grid = init_grid(2, 2);
    for (uint32_t i = 0; i < test_grid.rows; i++)
        for (uint32_t j = 0; j < test_grid.columns; j++)
            test_grid.field[i][j] = 1;

    int test = get_live_count(test_grid);
    ASSERT_EQUAL(4, test);
}

CTEST(GRAPHIC_TEST, get_center)
{
    char name[] = "Back";
    int test = get_center(20, name);
    ASSERT_EQUAL(8, test);
}
