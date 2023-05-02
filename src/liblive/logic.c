#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <liblive/logic.h>

Grid init_grid(uint32_t rows, uint32_t columns)
{
    bool** field = (bool**)malloc(sizeof(bool*) * rows);
    for (uint32_t i = 0; i < rows && field; i++) {
        field[i] = (bool*)calloc(sizeof(bool), columns);
        if (!field[i]) {
            for (uint32_t j = 0; j < i; j++) {
                free(field[j]);
            }
            free(field);
            field = NULL;
            break;
        }
    }
    Grid grid = {rows, columns, field};
    return grid;
}

int count_neighbors(Grid grid, uint32_t row, uint32_t column)
{
    int count = 0;
    for (uint32_t r = row - 1; r <= row + 1; r++) {
        for (uint32_t c = column - 1; c <= column + 1; c++) {
            if (r == row && c == column)
                continue;
            if (r < grid.rows && c < grid.columns) {
                if (grid.field[r][c] == 1)
                    count++;
            }
        }
    }
    return count;
}

int check_rules(Grid grid, uint32_t row, uint32_t column)
{
    int count = count_neighbors(grid, row, column);
    int status = grid.field[row][column];

    if (status) {
        if (count >= 2 && count <= 3)
            return 1;
        else
            return 0;
    }
    if (count == 3)
        return 1;
    return 0;
}

void merge_grid(Grid from_where, Grid to_here)
{
    for (uint32_t row = 0; row < from_where.rows; row++) {
        for (uint32_t column = 0; column < from_where.columns; column++) {
            to_here.field[row][column] = from_where.field[row][column];
        }
    }
}

void update_grid(Grid grid, Grid tmp)
{
    for (uint32_t row = 0; row < grid.rows; row++) {
        for (uint32_t column = 0; column < grid.columns; column++) {
            tmp.field[row][column] = check_rules(grid, row, column);
        }
    }
    merge_grid(tmp, grid);
}

void rand_grid(Grid grid)
{
    for (uint32_t i = 0; i < grid.rows; i++) {
        for (uint32_t j = 0; j < grid.columns; j++) {
            grid.field[i][j] = rand() % 2;
        }
    }
}

void free_grid(Grid grid)
{
    for (uint32_t i = 0; i < grid.rows; i++) {
        free(grid.field[i]);
    }
    free(grid.field);
}