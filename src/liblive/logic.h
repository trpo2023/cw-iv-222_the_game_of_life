#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct Grid {
    uint32_t rows, columns;
    bool** field;
} Grid;

Grid init_grid(uint32_t rows, uint32_t columns);
void rand_grid(Grid grid);
void free_grid(Grid grid);
void update_grid(Grid grid, Grid tmp);