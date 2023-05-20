#include <liblive/graphic.h>
#include <liblive/logic.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KEY_ESC 27

int main()
{
    /*/  Инициализация ncurses /*/
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    /*/ Включение режима отображения координат мыши /*/
    mouseinterval(0);
    curs_set(0);
    /*/ Инициализация переменных /*/
    pthread_t th_input, th_game;
    int row, col;
    getmaxyx(stdscr, row, col);
    Grid grid = init_grid(row, (col - MENU_SIZE) / 2);
    rand_grid(grid);
    GameStatus game = {row, col, L_MENU, B_START, 0, grid, {0}};
    /*/ создаем поток для обработки пользовательского ввода /*/
    pthread_create(&th_input, NULL, input_thread, &game);
    /*/ создаем поток для игры /*/
    pthread_create(&th_game, NULL, start_game, &game);
    while (true) {
        if (game.pressed == 1) {
            switch (game.btn) {
            case B_START:
                game.pressed = 0;
                game.location = L_GAME;
                game.btn = B_RESTART;
                break;
            case B_SETTINGS:
                game.pressed = 0;
                game.location = L_SETTINGS;
                game.btn = B_BACK;
                break;
            case B_RESTART:
                game.pressed = 0;
                rand_grid(grid);
                break;
            case B_BACK:
                game.pressed = 0;
                game.location = L_MENU;
                game.btn = B_START;
                break;
            case B_EXIT:
                /*/ Очистка ncurses и завершение программы /*/
                free_grid(grid);
                pthread_join(th_input, NULL);
                pthread_join(th_game, NULL);
                endwin();
                return 0;
            default:
                break;
            }
        }
        getmaxyx(stdscr, row, col); // получаем размер окна (стандартный экран)
        game.rows = row;
        game.columns = col;
        clear();
        draw_btns(&game);
        print_filed_v2(grid, '*');
        game.info.live = get_live_count(grid);
        mvprintw(game.rows / 3, game.columns - MENU_SIZE + 1, "Living cells: %d", game.info.live);
        refresh();
        usleep(100007);
    }

    return 0;
}