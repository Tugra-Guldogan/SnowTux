#ifndef LEVEL_H
#define LEVEL_H

#include "common.h"

extern bool checkWall(Coord c);
extern bool checkPlat(Coord c);
void drawLevel();
void loadLevel();

#endif
