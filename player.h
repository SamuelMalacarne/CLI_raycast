#ifndef H_PLAYER
#define H_PLAYER

#include "map.h"

typedef struct {
    double x, y, vel;
    double angle, rotVel;
} Player;

void updatePlayer(Map map, Player *p, int dir);
void drawPlayer(Map map, Player p);

#endif
