#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "map.h"
#include "util.h"

void initMap(Map *map, char *fileName) {
    int i, j;
    char ch;

    map->blockSize = BLOCK_SIZE;

    map->pf = fopen(fileName, "r");
    map->width = map->height = 0;
    if (!map->pf) {
        printf("ERROR: could not open `%s`\n", fileName);
        return;
    }

    while ((ch = fgetc(map->pf)) != '\n') {
        map->width++;
    }
    
    rewind(map->pf);
    ch = fgetc(map->pf);
    while (ch != EOF) {
        if (ch == '\n') map->height++;
        ch = fgetc(map->pf);
    }

    map->win = newwin((map->height * map->blockSize), (map->width * map->blockSize), 0, 0);

    rewind(map->pf);
    map->grid = malloc(map->height * sizeof(int *));
    for (i = 0; i < map->height; i++) {
        map->grid[i] = malloc(map->width * sizeof(int));
        j = 0;
        while ((ch = fgetc(map->pf)) != '\n') {
            map->grid[i][j++] = ch - '0';
        }
    }
}

void closeMap(Map *map) {
    fclose(map->pf);
    for (int i = 0; i < map->height; i++)
        free(map->grid[i]);
    free(map->grid);
    delwin(map->win);
}

void visMap(Map map) {
    int i, j, l, k;

    /*
    // draw a grid
    for (i = 0; i < map.width; i++)
        for (j = 0; j < map.height * map.blockSize; j++)
            mvwprintw(map.win, j, i * (map.blockSize), "|");

    for (i = 0; i < map.height; i++)
        for (j = 0; j < map.width * map.blockSize; j++)
            mvwprintw(map.win, i * (map.blockSize), j, "-");
    */

    // draw walls
    for (i = 0; i < map.height; i++) {
        for (l = 0; l < map.blockSize; l++) {
            for (j = 0; j < map.width; j++) {
                for (k = 0; k < map.blockSize; k++) {
                    if (map.grid[i][j] != 0) {
                        wattron(map.win, COLOR_PAIR(map.grid[i][j]));
                        mvwprintw(map.win, (i * map.blockSize)+l, (j * map.blockSize)+k, "#");
                        wattroff(map.win, COLOR_PAIR(map.grid[i][j]));
                    }
                }
            }
        }
    }

    // minimap border
    // box(map.win, 0, 0);
}

