#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"

typedef struct {
	SDL_Texture *texture;
	Coord offset;
	Coord size;
	SDL_RendererFlip flip;
} Sprite;

typedef struct {
	int red, green, blue, alpha;
} Colour;

typedef enum {
	COLOURISE_ABSOLUTE = 0,
	COLOURISE_ADDITIVE = 1
} ColourisationMethod;

extern SDL_Renderer *renderer;
extern SDL_Texture *renderBuffer;
extern Coord pixelGrid;
extern Coord screenBounds;

extern Colour makeColour(int red, int green, int blue, int alpha);
extern void *colouriseSprite(SDL_Surface *original, Colour colour, ColourisationMethod method);
extern SDL_Renderer *renderer;
extern void initGraphics();
extern void shutdownGraphics();
extern void processGraphics();
extern Sprite makeSprite(SDL_Texture *texture, Coord offset, SDL_RendererFlip flip);
extern void drawSpriteFull(Sprite sprite, Coord origin, double scalex, double scaley, double angle, bool centered);
extern void drawSprite(Sprite sprite, Coord origin);
extern Coord getTextureSize(SDL_Texture *texture);
extern Sprite makeFlippedSprite(char *textureName, SDL_RendererFlip flip);
extern Sprite makeSimpleSprite(char *textureName);
extern void drawSimpleSprite(char *textureName, Coord origin);
extern void drawSimpleSpriteFlipped(char *textureName, Coord origin, SDL_RendererFlip flip);
extern void drawSimpleTile(char *textureName, Coord origin);

#endif
