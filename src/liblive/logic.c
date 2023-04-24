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

int count_neighbors(Grid grid, int row, int column)
{
    int count = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = column - 1; c <= column + 1; c++) {
            if (r == row && c == column)
                continue;
            if (r >= 0 && r < grid.height && c >= 0 && c < grid.width) {
                if (grid.field[r][c] == 1)
                    count++;
            }
        }
    }
    return count;
}

int check_rules(Grid grid, int row, int column)
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

void rand_grid(Grid grid)
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