#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "player.h"
#include "ray.h"
#include "util.h"

void initialize() {
    initscr();              // inits the screen
    noecho();               // used to not print on the screen the user inputs
    curs_set(FALSE);        // 
    keypad(stdscr, TRUE);   // enables the arrow keys
    raw();                  // does not wait for the user to press enter for an input
    start_color();
    init_color(COLOR_CYAN, 600, 600, 600);
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
}

int main() {
    int width, height, ch;
    Map map;
    Player player = { .x = 1.5, .y = 1.5, .vel = 0.1, .angle = 350.0, .rotVel = 5.0 };
    WINDOW *gameWindow;

    initialize();
    initMap(&map, MAP_FILE);
    getmaxyx(stdscr, height, width);
    gameWindow = newwin(height, width, 0, 0);

    mvprintw(height/2, width/2 - 10, "Press any button to start");
    while ((ch = getch()) != 'q') {
        clear();
        wclear(map.win);

        updatePlayer(map, &player, ch);
  
        wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
        visMap(map);
        drawPlayer(map, player);
        castRay(map, player, width, height, gameWindow);
        refresh();
        wrefresh(map.win);
    }

    endwin();
    closeMap(&map);

    return 0;
}
