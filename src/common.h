#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern bool stopGame;
extern SDL_Window *window;

typedef struct {
	double x, y;
} Coord;

typedef struct {
    float x; 
    float y;
} point2;

typedef struct {
    float x; 
    float y; 
    float z;
} point3;

typedef struct {
    int r;
    int g;
    int b;
} color;

long getTime(void);
bool isDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms);
bool timer(long *lastTime, double hertz);
color makeColor(int r, int g, int b);
point2 makePoint2(float x, float y);
point3 makePoint3(float x, float y, float z);
float sineInc(float offset, float *sineInc, float speed, float magnitude);
int randomMq(int min, int max);
void fatalError(const char *title, const char *message);
char *combineStrings(const char *a, const char *b);
bool fileExists(const char *path);
extern Coord makeCoord(double x, double y);
extern Coord zeroCoord();

#endif
