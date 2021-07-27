#define _CRT_SECURE_NO_WARNINGS

#include "assets.h"
#include "graphics.h"
#include "level.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

const int BOUND = 16;

// Controls
bool movingRight = false;
bool movingLeft = false;

// Position
float playerX = 50;
float playerY = 50;
bool onGround = false;

// Jumping
const float JUMP_SPEED = 3.5f;
const float JUMP_SLOW = 0.1f;
bool jumpTry = false;
bool isJumping = false;
long lastJump = 0;
float jumpInc = 0;

// Physics
float GRAVITY = 1.5f;
const int FLOOR = 100;

// Animation
long lastAnimTime = 0;
int animInc = 0;
SDL_RendererFlip flip = SDL_FLIP_NONE;

bool isWalking() {
	return movingLeft || movingRight;
}

bool facing() {
	return movingLeft;
}

bool onFlat() {
	return playerY >= FLOOR;
}

void resetControls(void) {
	movingRight = false;
	movingLeft = false;
	jumpTry = false;
}

bool checkGround(Coord c) {
	return checkPlat(makeCoord(c.x, c.y + 5 + GRAVITY));
//	onGround = ((playerY + BOUND / 2) + GRAVITY >= FLOOR);
}

void applyControlsToPlayer(void) {
	if (movingRight && !checkWall(makeCoord(playerX - 5 - 1.0f, playerY))) {
		playerX -= 1.0f;
	}
	else if (movingLeft && !checkWall(makeCoord(playerX + 5 + 1.0f, playerY))) {
		playerX += 1.0f;
	}

	// Jumping

	// Start to jump
	if (jumpTry && onGround) {
		isJumping = true;
		lastJump = clock();
		jumpInc = JUMP_SPEED;
		onGround = false;
	}
	// Stop jumping
	if(isJumping && jumpInc == 0) {
		isJumping = false;
	}
	// Apply jumping
	if(isJumping) {
		playerY -= (jumpInc > 0 ? jumpInc -= JUMP_SLOW : 0);
	}
}

#define MAX_ENEMIES 5

typedef struct {
	bool valid;
	Coord pos;
} Enemy;

Enemy enemies[MAX_ENEMIES];

int enemyAnimInc = 0;
long lastEnemyAnimTime = 0;
int ENEMY_FRAMES = 2;

void enemyFrame() {
	// animate
	if (timer(&lastEnemyAnimTime, 250)) {
		enemyAnimInc = enemyAnimInc == ENEMY_FRAMES - 1 ? 0 : enemyAnimInc + 1;
	}
	char file[13];

	for (int i = 0; i < MAX_ENEMIES; i++) {
		if(!enemies[i].valid) continue;

		sprintf(file, "squid-0%d.png", enemyAnimInc+1);
		drawSimpleSprite(file, enemies[i].pos);

		if (!checkGround(enemies[i].pos)) {
			enemies[i].pos.y += GRAVITY/2;
		}
	}

	// todo: gravity
	// todo: player seek
	// todo: multiple
	// todo: facing dir
	// todo: spawn at map definition
	// todo: jump if above, within threshold (must be above another level)
	// todo: player spawn
}

void charFrame() {
	enemyFrame();
	onGround = checkGround(makeCoord(playerX, playerY));

	// Animation / flipping
	if (isWalking()) {
		if (isDue(lastAnimTime, 250)) {
			flip = facing() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
			if (onGround) {
				if (animInc == 3) {
					animInc = 0;
				} else {
					animInc++;
				}
			}
			lastAnimTime = clock();
		}
	}
	else {
		animInc = 1;
		lastAnimTime = 0;
	}

	// Draw sprite
	if (onGround) {
		switch (animInc) {
			case 0:
				drawSprite(makeSprite(getTexture("tux1-01.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 1:
				drawSprite(makeSprite(getTexture("tux1-02.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 2:
				drawSprite(makeSprite(getTexture("tux1-03.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 3:
				drawSprite(makeSprite(getTexture("tux1-02.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
		}
	} else {
		drawSprite(makeSprite(getTexture("tux1-jump.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
	}

	// Falling
	if (!onGround) {
		playerY += GRAVITY;
	}
}

void spawnChar(Coord c) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if(enemies[i].valid) continue;
		enemies[i].valid = true;
		enemies[i].pos = c;
		break;
	}
}

void initCharacters() {
}
