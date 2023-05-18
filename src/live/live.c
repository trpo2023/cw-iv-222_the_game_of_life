#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <liblive/graphic.h>
#include <liblive/logic.h>

#define KEY_ESC 27

int main()
{
    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Включение режима отображения координат мыши
    mouseinterval(0);
    curs_set(0);

    /*/ Инициализация переменных /*/
    pthread_t th_input, th_game;
    int rows, columns;
    getmaxyx(stdscr, rows, columns);
    GameStatus game = {rows, columns - MENU_SIZE, L_MENU, B_START, 0};
    Grid grid = init_grid(game.rows, game.columns / 2);
    rand_grid(grid);

    /*/ создаем поток для обработки пользовательского ввода /*/
    pthread_create(&th_input, NULL, input_thread, &game);
    /*/ создаем поток для игры /*/
    GameThread th_arg = {&game, grid};
    pthread_create(&th_game, NULL, start_game, &th_arg);

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
        clear();
        draw_btns(&game);
        print_filed_v2(grid, '*');
        refresh();
        usleep(100000);
    }

    return 0;
}
