#include "common.h"
#include <time.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
SDL_Window *window = NULL;
bool stopGame = false;
float RADIAN_CIRCLE = 3.141592 * 2;

Coord zeroCoord() {
	return makeCoord(0, 0);
}

Coord makeCoord(double x, double y) {
	Coord coord = { x, y };
	return coord;
}

long getTime(void) {
	return clock() / (CLOCKS_PER_SEC / 1000);		// convert ticks to milliseconds
}

bool isDue(long timeOfLastOperation, float timeUntilNextOperation) {
	return (getTime() - timeOfLastOperation) >= timeUntilNextOperation;
}

bool timer(long *lastTime, double hertz) {
	long now = clock();
	if (isDue(*lastTime, hertz)) {
		*lastTime = now;
		return true;
	}
	else {
		return false;
	}
}

color makeColor(int r, int g, int b) {
    color c = { r, g, b };
    return c;
}

point2 makePoint2(float x, float y) {
    point2 p = { x, y };
    return p;
}

point3 makePoint3(float x, float y, float z) {
    point3 p = { x, y, z };
    return p;
}

float sineInc(float offset, float *sineInc, float speed, float magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    float sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

void fatalError(const char *title, const char *message) {
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,
		title,
		message,
		window
	);
	SDL_Quit();
}

char *combineStrings(const char *a, const char *b) {
	//Allocate exact amount of space necessary to hold the two strings.
	char *result = malloc(strlen(a) + strlen(b) + 1);		//+1 for the zero-terminator
#pragma warning(disable: 4996)
	strcpy(result, a);
	strcat(result, b);
#pragma warning(default: 4996)

	return result;
}

bool fileExists(const char *path) {
	return fopen(path, "r");
}
