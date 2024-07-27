all:
	gcc main.c map.c player.c ray.c util.c -o raycast -lm -lncurses -Wall
