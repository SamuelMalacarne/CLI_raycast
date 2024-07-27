#ifndef H_MAP
#define H_MAP

#include <stdio.h>
#include <ncurses.h>

typedef struct {
    FILE *pf;
    WINDOW *win;
    int **grid;
    int width, height;
    double blockSize;
} Map;

void initMap(Map *map, char *fileName);
void closeMap(Map *map);
void visMap(Map map);

#endif
