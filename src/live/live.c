#include <stdio.h>
#include <stdlib.h>

#include <liblive/graphic.h>
#include <liblive/logic.h>

int main()
{
    Grid grid = init_grid(25, 80);
    Grid tmp = init_grid(grid.rows, grid.columns);
    rand_grid(grid);

    while (true) {
        system("clear");
        print_field(grid, '*');
        int count_live_cells = get_live_count(grid);
        printf("\n\t\t\tКоличество живых клнток: %d\n", count_live_cells);
        update_grid(grid, tmp);
    }

    return 0;
}
