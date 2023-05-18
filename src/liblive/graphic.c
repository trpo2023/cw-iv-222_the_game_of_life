#include <liblive/graphic.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// Вывод игрового поля
void print_field(Grid grid, char symbol)
{
    double start = wtime();
    printf("Hello World %d %d %p\n", grid.rows, grid.columns, grid.field);
    for (uint32_t i = 0; i < grid.rows; i++) {
        for (uint32_t j = 0; j < grid.columns; j++) {
            if (grid.field[i][j])
                printf("%c ", symbol);
            else
                printf("  ");
        }
        printf("\n");
    }
    double time = wtime() - start;
    printf("\t\t\tВремя вывода игрового поля: %lf\n", time);
}

//Количество живых клеток на игровом поле
int get_live_count(Grid grid)
{
    int count = 0;
    for (uint32_t i = 0; i < grid.rows; i++) {
        for (uint32_t j = 0; j < grid.columns; j++) {
            if (grid.field[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

void print_filed_v2(Grid grid, char symbol)
{
    for (uint32_t row = 0; row < grid.rows; row++) {
        for (uint32_t column = 0; column < grid.columns; column++) {
            if (grid.field[row][column])
                mvprintw(row, column * 2, "%c", symbol);
        }
    }
}

void create_menu(GameStatus* game)
{
    for (int row = 0; row < game->rows; row++) {
        mvprintw(row, game->columns, "|");
    }
}

int get_center(int size, char* str)
{
    return size / 2 - strlen(str) / 2;
}

void draw_btns(GameStatus* game)
{
    create_menu(game);
    char* location_name;
    Btn btns[10];
    int count;
    switch (game->location) {
    case L_MENU:
        location_name = "Menu";
        btns[0].name = "Start";
        btns[0].id = B_START;
        btns[1].name = "Settings";
        btns[1].id = B_SETTINGS;
        btns[2].name = "Exit";
        btns[2].id = B_EXIT;
        count = 3;
        break;
    case L_GAME:
        location_name = "Game";
        btns[0].name = "Restart";
        btns[0].id = B_RESTART;
        btns[1].name = "Back";
        btns[1].id = B_BACK;
        count = 2;
        break;
    case L_SETTINGS:
        location_name = "Settings";
        btns[0].name = "Save";
        btns[0].id = B_SAVE;
        btns[1].name = "Back";
        btns[1].id = B_BACK;
        count = 2;
        break;
    default:
        return;
    }
    int center = game->columns + get_center(MENU_SIZE, location_name);
    mvprintw(0, center, "%s", location_name);

    int center_row = (game->rows - count) / 2;
    for (int i = 0; i < count; i++) {
        if (game->btn == btns[i].id) {
            mvprintw(center_row + i, game->columns + 1, ">", game->btn);
            mvprintw(center_row + i, game->columns + MENU_SIZE - 1, "<");
        }
        int center = game->columns + get_center(MENU_SIZE, btns[i].name);
        mvprintw(center_row + i, center, "%s", btns[i].name);
    }
}

void* input_thread(void* arg)
{
    GameStatus* game = (GameStatus*)arg;
    int columns, rows;
    int ch;
    MEVENT event;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
        case KEY_DOWN:
        case KEY_UP:
            switch (game->location) {
            case L_MENU:
                if (ch == KEY_UP && (game->btn > B_START)
                    && (game->btn <= B_EXIT))
                    game->btn -= 1;
                if (ch == KEY_DOWN && (game->btn >= B_START)
                    && (game->btn < B_EXIT))
                    game->btn += 1;
                break;
            case L_GAME:
                if (ch == KEY_UP && (game->btn > B_RESTART)
                    && (game->btn <= B_BACK))
                    game->btn -= 1;
                if (ch == KEY_DOWN && (game->btn >= B_RESTART)
                    && (game->btn < B_BACK))
                    game->btn += 1;
                break;
            case L_SETTINGS:
                if (ch == KEY_UP && (game->btn > B_BACK)
                    && (game->btn <= B_SAVE))
                    game->btn -= 1;
                if (ch == KEY_DOWN && (game->btn >= B_BACK)
                    && (game->btn < B_SAVE))
                    game->btn += 1;
                break;

            default:
                break;
            }
            break;
        case '\n':
            game->pressed = 1;
            if (game->location == L_MENU && game->btn == B_EXIT)
                return 0;
            break;
        case KEY_ESC:
            game->location = L_MENU;
            game->btn = B_EXIT;
            game->pressed = 1;
            return 0;
        case KEY_MOUSE:
            getmouse(&event);
            // int x = event.x;
            // int y = event.y;
            break;
        default:
            break;
        }
        getmaxyx(
                stdscr,
                rows,
                columns); // получаем размер окна (стандартный экран)
        game->rows = rows;
        game->columns = columns - MENU_SIZE;
        refresh();
    }
    return 0;
}

void* start_game(void* arg)
{
    GameThread* get_arg = (GameThread*)arg;
    GameStatus* game = get_arg->game;
    Grid grid = get_arg->grid;
    Grid tmp = init_grid(grid.rows, grid.columns);

    while (true) {
        usleep(100000);
        if (game->pressed && game->location == L_MENU && game->btn == B_EXIT) {
            free_grid(tmp);
            return 0;
        }
        if (game->location != L_GAME)
            continue;

        clear();
        print_filed_v2(grid, '*');
        draw_btns(game);
        refresh();
        update_grid(grid, tmp);
    }
}
