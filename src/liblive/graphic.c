#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <liblive/logic.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// Вывод игрового поля
void print_field(Grid grid)
{
    double start = wtime();
    printf("Hello World %d %d %p\n", grid.height, grid.width, grid.field);
    for (uint32_t i = 0; i < grid.height; i++) {
        for (uint32_t j = 0; j < grid.width; j++) {
            printf("%d ", grid.field[i][j]);
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
    for (uint32_t i = 0; i < grid.height; i++) {
        for (uint32_t j = 0; j < grid.width; j++) {
            if (grid.field[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
