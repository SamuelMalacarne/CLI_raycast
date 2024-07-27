#ifndef H_UTIL
#define H_UTIL

#define PI 3.14159265358979323846
#define PI_180 PI/180.0

#define BLOCK_SIZE 1.0
#define MAP_FILE "maps/maze.txt"

#define FOV 60.0
#define ANGLE_INCREMENT 0.1

typedef struct {
    double x, y;
} Vec2;

double deg2rad(double deg);

#endif
