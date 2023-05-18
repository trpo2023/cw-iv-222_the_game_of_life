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

    // Очистка ncurses и завершение программы
    endwin();
    return 0;
}
