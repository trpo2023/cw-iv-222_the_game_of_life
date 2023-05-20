#pragma once
#include <liblive/logic.h>

#define MENU_SIZE 20
#define KEY_ESC 27

typedef struct GridStatus{
    int live;
    //double time;
} GridStatus;
typedef struct GameStatus {
    int rows, columns;
    int location, btn;
    int pressed;
    Grid grid;
    GridStatus info;
} GameStatus;

typedef struct Btn {
    char* name;
    int id;
} Btn;

enum locations { L_MENU, L_SETTINGS, L_GAME };

enum menu_btns {
    B_START,
    B_SETTINGS,
    B_EXIT,
    B_RESTART,
    B_BACK,
};

double wtime();
int get_center(int size, char* str);
int get_live_count(Grid grid);
void print_field(Grid grid, char symbol);
void print_filed_v2(Grid grid, char symbol);
void create_menu(GameStatus* game);
void draw_btns(GameStatus* game);
void* input_thread(void* arg);
void* start_game(void* arg);