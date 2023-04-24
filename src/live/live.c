#include <stdio.h>
#include <stdlib.h>

#include <liblive/graphic.h>
#include <liblive/logic.h>

int main()
{
    Grid grid = init_grid(50, 50);
    rand_grid(grid);

    print_field(grid, '*');
    int count_live_cells = get_live_count(grid);
    printf("\t\t\tКоличество живых клнток: %d\n", count_live_cells);
    free_grid(grid);
    return 0;
}
