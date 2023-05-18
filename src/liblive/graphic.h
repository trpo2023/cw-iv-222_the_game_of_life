#pragma once
#include <liblive/logic.h>

typedef struct GameStatus {
    int rows, columns;
    int location, btn;
    int pressed;
} GameStatus;


double wtime();
int get_live_count(Grid grid);
void print_field(Grid grid, char symbol);