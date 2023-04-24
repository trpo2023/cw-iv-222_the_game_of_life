#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct Grid {
    uint32_t width, height;
    bool** field;
} Grid;

Grid init_grid(uint32_t width, uint32_t height);
void rand_grid(Grid grid);
void free_grid(Grid grid);
int count_neighbors(Grid grid, int row, int column);