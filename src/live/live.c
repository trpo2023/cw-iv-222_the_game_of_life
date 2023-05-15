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

    int y, x;
    // Цикл чтения событий мыши и клавиатуры
    int ch;
    MEVENT event;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
        case KEY_UP:
            mvprintw(1, 0, "UP   ");
            break;
        case KEY_DOWN:
            mvprintw(1, 0, "DOWN ");
            break;
        case '\n':
            mvprintw(1, 0, "ENTER");
            break;
        case KEY_ESC:
            mvprintw(1, 0, "ESC  ");
            break;
        case KEY_MOUSE:
            getmouse(&event);
            int x = event.x;
            int y = event.y;
            mvprintw(2, 0, "MOUSE: (%d %d)     ", x, y);
            break;
        default:
            break;
        }
        getmaxyx(stdscr, y, x); // получаем размер окна (стандартный экран)
        mvprintw(
                0,
                0,
                "console size: %d %d     ",
                y,
                x); // выводим размер консоли
    }

    // Очистка ncurses и завершение программы
    endwin();
    return 0;

    Grid grid = init_grid(35, 80);
    Grid tmp = init_grid(grid.rows, grid.columns);
    rand_grid(grid);

    int old_count_live = 0;
    int count_live_cells = get_live_count(grid);
    int count = 0;
    int iterations = 0;

    while (true) {
        if (old_count_live == count_live_cells)
            count++;
        else
            count = 0;

        if (count > 30) {
            free_grid(grid);
            free_grid(tmp);
            return 0;
        }
        system("clear");
        print_field(grid, '*');
        count_live_cells = get_live_count(grid);
        printf("\n\t\t\tКоличество живых клеток: %d\n\n\t\t\tПовторов: "
               "%d\n\n\t\t\tИтераций: %d\n",
               count_live_cells,
               count,
               iterations);
        update_grid(grid, tmp);
        old_count_live = get_live_count(grid);
        usleep(100000);
        iterations++;
    }

    return 0;
}
