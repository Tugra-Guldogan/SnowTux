#include <stdlib.h>
#include <SDL_Image.h>
#include "assets.h"
#include "common.h"
#include "graphics.h"
#include "input.h"
#include "characters.h"
#include "level.h"
#include <time.h>

const char* WINDOW_TITLE = "SnowTux";
const int FRAMES_PER_SECOND = 60;

static void shutdownSdl(void) {
    shutdownGraphics();
    SDL_DestroyWindow(window);

    window = NULL;

    SDL_Quit();
}

static void startSdl(void) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    initGraphics();
    atexit(shutdownSdl);
}

int main(int argc, char *argv[]) {
	startSdl();

	initAssets();
	loadLevel();
	initCharacters();

	long timeOfLastFrame_ms = 0;
    float timeUntilNextFrame_ms = (float)1000 / (float)FRAMES_PER_SECOND;

    while (!stopGame) {
		if(!isDue(timeOfLastFrame_ms, timeUntilNextFrame_ms)) {
			continue;
		}

		checkForInputAndEvents();
		applyControlsToPlayer();
		charFrame();
		processGraphics();
		drawLevel();

		timeOfLastFrame_ms = getTime();
    }

    return 0; // no errors
}
