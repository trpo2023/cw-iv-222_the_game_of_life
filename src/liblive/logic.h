#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct Grid {
    uint32_t rows, columns;
    bool** field;
} Grid;

Grid init_grid(uint32_t rows, uint32_t columns);
int count_neighbors(Grid grid, uint32_t row, uint32_t column);
int check_rules(Grid grid, uint32_t row, uint32_t column);
void merge_grid(Grid from_where, Grid to_here);
void rand_grid(Grid grid);
void free_grid(Grid grid);
void update_grid(Grid grid);