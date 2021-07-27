#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>

#define ASSET_VERSIONS 2
typedef enum {
	ASSET_DEFAULT = 0,
	ASSET_WHITE = 1
} AssetVersion;

typedef struct {
	char* key;
	SDL_Texture* textures[ASSET_VERSIONS];
} Asset;

//typedef struct {
//	char* key;
//	Mix_Chunk* sound;
//} SoundAsset;

extern void initAssets(void);
extern SDL_Texture *getTexture(char *path);
extern SDL_Texture *getTextureVersion(char *path, AssetVersion version);
extern Asset getAsset(char *path);
extern void shutdownAssets(void);
//extern SoundAsset getSound(char *path);
//extern void playOn(char* path, int channel);
//extern void play(char* path);
extern SDL_Texture *getTexture(char *path);

#endif
