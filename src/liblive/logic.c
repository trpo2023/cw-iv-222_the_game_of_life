#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <liblive/logic.h>

Grid init_grid(uint32_t width, uint32_t height)
{
    bool** field = (bool**)malloc(sizeof(bool*) * height);
    for (uint32_t i = 0; i < width && field; i++) {
        field[i] = (bool*)calloc(sizeof(bool), width);
        if (!field[i]) {
            for (uint32_t j = 0; j < i; j++) {
                free(field[j]);
            }
            free(field);
            field = NULL;
            break;
        }
    }
    Grid grid = {width, height, field};
    return grid;
}

void rand_grind(Grid grid)
{
    for (uint32_t i = 0; i < grid.height; i++) {
        for (uint32_t j = 0; j < grid.height; j++) {
            grid.field[i][j] = rand() % 2;
        }
    }
}

void free_grid(Grid grid)
{
    for (uint32_t i = 0; i < grid.height; i++) {
        free(grid.field[i]);
    }
    free(grid.field);
}