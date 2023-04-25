#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <liblive/graphic.h>
#include <liblive/logic.h>

int main()
{
    Grid grid = init_grid(35, 80);
    Grid tmp = init_grid(grid.rows, grid.columns);
    rand_grid(grid);

    int old_count_live = 0;
    int count_live_cells = get_live_count(grid);
    int count = 0;

    while (true) {
        if (old_count_live == count_live_cells)
            count++;
        else
            count = 0;

        if (count > 30) {
            free_grid(grid);
            free_grid(tmp);
            return 0;
        }
        system("clear");
        print_field(grid, '*');
        count_live_cells = get_live_count(grid);
        printf("\n\t\t\tКоличество живых клнток: %d\n\n\t\t\tПовторов: %d\n",
               count_live_cells,
               count);
        update_grid(grid, tmp);
        old_count_live = get_live_count(grid);
        usleep(100000);
    }

    return 0;
}
