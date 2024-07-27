#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ncurses.h>
#include "ray.h"
#include "util.h"

double distance(Vec2 point, double playerx, double playery) {
    return sqrt(pow(point.x - playerx, 2.0) + pow(point.y - playery, 2.0));
}

bool inBound(int x, int y, Map m) {
    return (x >= 0 && x < m.width && y >= 0 && y < m.height);
}

void drawLine(Map map, double offset, double dist, int width, int height, Vec2 hit) {
    double lineHeight = (dist > 1.0) ? height/dist : height, lineWidth = width * (ANGLE_INCREMENT / FOV);
    double startX = width - (offset + (FOV/2.0)) * (width / FOV), startY = (height/2.0) - (lineHeight/2.0);
    double i, j;

    for (i = 0.0; i < lineHeight && i < height; i += 1.0)
        for (j = 0.0; j < lineWidth; j += 1.0)
            mvprintw(startY + i, startX + j, "@");
}

void getGridIndex(int *gx, int *gy, Vec2 pt, double angle, bool vertical) {
    *gx = (int)pt.x - (((90.0 < angle && angle < 270.0 && !vertical) ? 1 : 0));
    *gy = (int)pt.y - (((0.0 < angle && angle < 180.0 && vertical) ? 1 : 0));
}

void castRay(Map map, Player p, int width, int height, WINDOW *win) {
    Vec2 p1, p2, vertStart, horizStart;
    double i, dist1, dist2, angle, slope, offset, vd, hd;
    int gridX, gridY;

    for (offset = -FOV/2.0; offset <= FOV/2.0; offset += ANGLE_INCREMENT) {
        angle = p.angle + offset;
        slope = tan(deg2rad(angle));
     
        vertStart.x = (90 < angle && angle < 270) ? floor(p.x) : ceil(p.x);
        vertStart.y = p.y - ((vertStart.x - p.x) * slope);
        vd = (90 < angle && angle < 270) ? slope : (-1.0 * slope);
        getGridIndex(&gridX, &gridY, vertStart, angle, false);
        if (inBound(gridX, gridY, map) && map.grid[gridY][gridX] != 0) {
            p1 = vertStart;
        } else {
            for (i = 1.0; i < 100.0; i += 1.0) {
                p1.y = vertStart.y + (vd * i);
                p1.x = vertStart.x - ((90 < angle && angle < 270) ? i : (-1.0 * i));
                getGridIndex(&gridX, &gridY, p1, angle, false);
                if (inBound(gridX, gridY, map) && map.grid[gridY][gridX] != 0) break;
            }
        }
    
        horizStart.y = (0 < angle && angle < 180) ? floor(p.y) : ceil(p.y);
        horizStart.x = ((p.y - horizStart.y) / slope) + p.x;
        hd = (0 < angle && angle < 180) ? (1.0 / slope) : (-1.0 / slope);
        getGridIndex(&gridX, &gridY, horizStart, angle, true);
        if (inBound(gridX, gridY, map) && map.grid[gridY][gridX] != 0) {
            p2 = horizStart;
        } else {
            for (i = 1.0; i < 100.0; i += 1.0) {
                p2.y = horizStart.y - ((0 < angle && angle < 180) ? i : (-1.0 * i));
                p2.x = horizStart.x + (hd * i);
                getGridIndex(&gridX, &gridY, p2, angle, true);
                if (inBound(gridX, gridY, map) && map.grid[gridY][gridX] != 0) break;
            }
        }
    
        dist1 = distance(p1, p.x, p.y);
        dist2 = distance(p2, p.x, p.y);
        if (dist1 < dist2) {
            getGridIndex(&gridX, &gridY, p1, angle, !(90 < angle && angle < 270));
            attron(COLOR_PAIR(1));
            drawLine(map, offset, dist1 * cos(deg2rad(abs(offset))), width, height, p1);
            attroff(COLOR_PAIR(1));
        } else {
            getGridIndex(&gridX, &gridY, p2, angle, (0 < angle && angle < 180));
            attron(COLOR_PAIR(2));
            drawLine(map, offset, dist2 * cos(deg2rad(abs(offset))), width, height, p2);
            attroff(COLOR_PAIR(2));
        }
    }
}
