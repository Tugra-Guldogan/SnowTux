  
#ifndef CHAR_H
#define CHAR_H

extern void charFrame();

#include "common.h"
#include <stdbool.h>
#include <SDL_opengl.h>

extern float playerX;
extern float playerY;

extern bool movingRight;
extern bool movingLeft;
extern bool jumpTry;

void spawnChar(Coord c);
void resetControls(void);
void applyControlsToPlayer(void);
void initCharacters();

#endif
