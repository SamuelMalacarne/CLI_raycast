#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ncurses.h>
#include "player.h"
#include "map.h"
#include "util.h"

void updatePlayer(Map map, Player *p, int dir) {
    double newY, newX;

    switch (dir) {
        case 'w':
            newY = p->y - (sin(deg2rad(p->angle)) * p->vel);
            newX = p->x + (cos(deg2rad(p->angle)) * p->vel);
        break;

        case 's':
            newY = p->y + (sin(deg2rad(p->angle)) * p->vel);
            newX = p->x - (cos(deg2rad(p->angle)) * p->vel);
        break;
        
        case 'a':
            newY = p->y + (sin(deg2rad(p->angle - 90.0)) * p->vel);
            newX = p->x - (cos(deg2rad(p->angle - 90.0)) * p->vel);
        break;
        
        case 'd':
            newY = p->y + (sin(deg2rad(p->angle + 90.0)) * p->vel);
            newX = p->x - (cos(deg2rad(p->angle + 90.0)) * p->vel);
        break;

        case KEY_LEFT:
            p->angle += p->rotVel;
            if (p->angle >= 360.0) p->angle = p->angle - 360.0;
        break;

        case KEY_RIGHT:
            p->angle -= p->rotVel;
            if (p->angle <= 0.0) p->angle = 360.0 - p->angle;
        break; 
    }

    if (map.grid[(int)floor(newY)][(int)floor(newX)] == 0) {
        p->y = newY;
        p->x = newX;
    }
}

char getSprite(Player p) {
    double a = p.angle;
    if (a <= 45.0 || a >= 315.0 ) {
        return '>';
    } else if (a > 45.0 && a <= 135.0) {
        return '^';
    } else if (a > 135.0 && a <= 225.0) {
        return '<';
    } else if (a > 225.0 && a < 315.0) {
        return 'v';
    }
    return '.';
}

void drawPlayer(Map map, Player p) {
    /*
    double i, x, y, slope = tan(deg2rad(p.angle));
    for (i = 0.0; i <= 10.0; i += 0.5) {
        x = p.x - ((90 < p.angle && p.angle < 270) ? i : (-1.0 * i));
        y = p.y - ((90 < p.angle && p.angle < 270) ? (-1.0 * i * slope) : (i * slope));
        mvwprintw(map.win, map.blockSize * y, map.blockSize * x, "*");
    }
    */

    mvwprintw(map.win, (map.blockSize * p.y), (map.blockSize * p.x), "%c", getSprite(p));
}




