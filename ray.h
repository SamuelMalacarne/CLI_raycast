#ifndef H_RAY
#define H_RAY

#include <ncurses.h>
#include "map.h"
#include "player.h"

void castRay(Map map, Player p, int width, int height, WINDOW *win);

#endif
