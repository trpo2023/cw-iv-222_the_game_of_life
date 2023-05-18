#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#include <liblive/graphic.h>

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

