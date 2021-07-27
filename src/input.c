#include "common.h"
#include "characters.h"

void checkForInputAndEvents(void) {
	resetControls();
	SDL_PumpEvents();							// prepare SDL for event checking

    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			// system events
			case SDL_QUIT:
				stopGame = true;
				break;

			// single key presses
			case SDL_KEYDOWN: {
				if (event.key.repeat) {
					break;
				}

				SDL_Keycode keypress = event.key.keysym.scancode;
				if (keypress == SDL_SCANCODE_ESCAPE) {
					stopGame = true;
				}
				if (keypress == SDL_SCANCODE_SPACE) {
					jumpTry = true;
				}
			}
		}
	}

	// held keys
	const Uint8 *heldKeys = SDL_GetKeyboardState(NULL);
	if (heldKeys[SDL_SCANCODE_LEFT]) {
		movingRight = true;
	} else if (heldKeys[SDL_SCANCODE_RIGHT]) {
		movingLeft = true;
	}
}
