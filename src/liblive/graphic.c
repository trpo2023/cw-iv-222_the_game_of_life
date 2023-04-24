#include "logic.h"
#include "graphic.h"

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}


//Количество живых клеток на игровом поле
int get_live_count(Grid grid)
{
    int count = 0;
    for (int i = 0; i < __WORLD_WIDTH__; i++) {
        for (int j = 0; j < __WORLD_HEIGHT__; j++) {
            if (grid.field[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
