#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <liblive/graphic.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
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
        mvprintw(row, game->columns - MENU_SIZE, "|");
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
        btns[0].name = "Back";
        btns[0].id = B_BACK;
        count = 1;
        break;
    default:
        return;
    }
    int center
            = game->columns - MENU_SIZE + get_center(MENU_SIZE, location_name);
    mvprintw(0, center, "%s", location_name);

    int center_row = (game->rows - count) / 2;
    for (int i = 0; i < count; i++) {
        if (game->btn == btns[i].id) {
            mvprintw(
                    center_row + i,
                    game->columns - MENU_SIZE + 1,
                    ">",
                    game->btn);
            mvprintw(center_row + i, game->columns - 1, "<");
        }
        int center = game->columns - MENU_SIZE
                + get_center(MENU_SIZE, btns[i].name);
        mvprintw(center_row + i, center, "%s", btns[i].name);
    }
}

void* input_thread(void* arg)
{
    GameStatus* game = (GameStatus*)arg;
    int ch;
    int oldx = 0, oldy = 0;
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
            if (game->location == L_SETTINGS) {
                getmouse(&event);
                int x = event.x / 2;
                int y = event.y;
                if (x == oldx && y == oldy)
                    break;
                if ((int)game->grid.rows > y && (int)game->grid.columns > x) {
                    if (game->grid.field[y][x] == 1)
                        game->grid.field[y][x] = 0;
                    else
                        game->grid.field[y][x] = 1;
                }
                oldx = x, oldy = y;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

void* start_game(void* arg)
{
    GameStatus* game = (GameStatus*)arg;

    while (true) {
        usleep(100000);
        if (game->pressed && game->location == L_MENU && game->btn == B_EXIT) {
            return 0;
        }
        if (game->location != L_GAME)
            continue;
        game->info.live++;
        update_grid(game->grid);
    }
}
