#pragma once
#include <liblive/logic.h>

typedef struct GameStatus {
    int rows, columns;
    int location, btn;
    int pressed;
} GameStatus;

enum locations { L_MENU, L_SETTINGS, L_GAME };

enum menu_btns {
    B_START,
    B_SETTINGS,
    B_EXIT,
    B_RESTART,
    B_BACK,
    B_SAVE,
};

typedef struct GameThread {
    GameStatus *game;
    Grid grid;
} GameThread;

typedef struct Btn {
    char *name;
    int id;
} Btn;

double wtime();
int get_live_count(Grid grid);
void print_field(Grid grid, char symbol);
void print_filed_v2(Grid grid, char symbol);
int get_center(int size, char *str);
void create_menu(GameStatus *game);
void draw_btns(GameStatus* game);