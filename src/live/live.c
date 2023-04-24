#include <stdio.h>
#include <stdlib.h>

#include <liblive/graphic.h>
#include <liblive/logic.h>

int main()
{
    Grid grid = init_grid(50, 50);
    rand_grind(grid);
    printf("Hello World %d %d %p\n", grid.height, grid.width, grid.field);

    for (uint32_t i = 0; i < grid.height; i++) {
        for (uint32_t j = 0; j < grid.width; j++) {
            printf("%d ", grid.field[i][j]);
        }
        printf("\n");
    }

    free_grid(grid);
    return 0;
}
