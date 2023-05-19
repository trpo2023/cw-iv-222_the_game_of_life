#include <liblive/logic.h>

#include <ctest.h>

CTEST(LOGIC_TEST, init_grid)
{
    Grid grid = init_grid(2, 5);

    ASSERT_EQUAL(2, grid.rows);
    ASSERT_EQUAL(5, grid.columns);

    free_grid(grid);
}

CTEST(LOGIC_TEST, count_neighbors)
{
    Grid grid = init_grid(3, 3);
    for (uint32_t i = 0; i < grid.rows; i++)
        for (uint32_t j = 0; j < grid.columns; j++)
            grid.field[i][j] = 1;

    int test1 = count_neighbors(grid, 0, 0);
    int test2 = count_neighbors(grid, 1, 1);
    int test3 = count_neighbors(grid, 0, 1);

    ASSERT_EQUAL(3, test1);
    ASSERT_EQUAL(8, test2);
    ASSERT_EQUAL(5, test3);

    free_grid(grid);
}

CTEST(LOGIC_TEST, check_rules)
{
    Grid grid = init_grid(3, 3);
    for (uint32_t i = 0; i < grid.rows; i++)
        for (uint32_t j = 0; j < grid.columns; j++)
            grid.field[i][j] = 1;

    int test1 = check_rules(grid, 0, 0);
    int test2 = check_rules(grid, 1, 1);
    int test3 = check_rules(grid, 0, 1);

    ASSERT_EQUAL(1, test1);
    ASSERT_EQUAL(0, test2);
    ASSERT_EQUAL(0, test3);

    free_grid(grid);
}

CTEST(LOGIC_TEST, merge_grid)
{
    Grid grid = init_grid(3, 3);
    for (uint32_t i = 0; i < grid.rows; i++)
        for (uint32_t j = 0; j < grid.columns; j++)
            grid.field[i][j] = 1;

    Grid grid2 = init_grid(3, 3);
    merge_grid(grid, grid2);
    int status = 0;
    for (uint32_t i = 0; i < grid.rows; i++)
        for (uint32_t j = 0; j < grid.columns; j++)
            if (grid.field[i][j] != grid2.field[i][j])
                status = 1;

    ASSERT_EQUAL(0, status);

    free_grid(grid);
    free_grid(grid2);
}

CTEST(LOGIC_TEST, update_grid)
{
    Grid grid = init_grid(3, 3);
    for (uint32_t i = 0; i < grid.rows; i++)
        for (uint32_t j = 0; j < grid.columns; j++)
            grid.field[i][j] = 1;

    update_grid(grid);

    ASSERT_EQUAL(1, grid.field[0][0]);
    ASSERT_EQUAL(0, grid.field[1][1]);
    ASSERT_EQUAL(0, grid.field[0][1]);

    free_grid(grid);
}