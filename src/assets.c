#include <assert.h>
#include <stdbool.h>
#include "assets.h"
#include "graphics.h"
#include <string.h>
#include <SDL_Image.h>
// #include <SDL_Mixer.h>

typedef struct {
	char* filename;
	bool makeWhiteVersion;
} AssetDef;

typedef struct {
	char* filename;
	int volume;
} SoundDef;

static char* assetPath;
static Asset *assets;
static int assetCount;
//static SoundAsset *sounds;
//static int soundCount;

//SoundAsset getSound(char *path) {
//	//Loop through register until key is found, or we've exhausted the array's iteration.
//	for (int i = 0; i < soundCount; i++) {
//		if (strcmp(sounds[i].key, path) == 0)			//if strings match.
//			return sounds[i];
//	}
//
//	fatalError("Could not find Asset in register", path);
//}

static Asset makeAsset(AssetDef definition) {
	assert(renderer != NULL);

	char *absPath = combineStrings(assetPath, definition.filename);
	//Check existence on file system.
	if (!fileExists(absPath))
		fatalError("Could not find Asset on disk", absPath);

	//Load file from disk.
	SDL_Surface *original = IMG_Load(absPath);
	free(absPath);

	Asset asset = { definition.filename };

	//Build initial texture and assign.
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, original);

	asset.textures[ASSET_DEFAULT] = texture;

	// make a white version
	if (definition.makeWhiteVersion) {
		colouriseSprite(original, makeColour(255, 0, 0, 255), 1 /* additive */);
		SDL_Texture *hitTexture = SDL_CreateTextureFromSurface(renderer, original);
		asset.textures[ASSET_WHITE] = hitTexture;
	}

	return asset;
}

SDL_Texture *getTexture(char *path) {
	return getTextureVersion(path, ASSET_DEFAULT);
}
SDL_Texture *getTextureVersion(char *path, AssetVersion version) {
	return getAsset(path).textures[version];
}
Asset getAsset(char *path) {
	//Loop through register until key is found, or we've exhausted the array's iteration.
	for (int i = 0; i < assetCount; i++) {
		if (strcmp(assets[i].key, path) == 0)			//if strings match.
			return assets[i];
	}

	fatalError("Could not find Asset in register", path);
}

void shutdownAssets(void) {
	free(assetPath);
	free(assets);

	//for (int i = 0; i < soundCount; i++) Mix_FreeChunk(sounds[i].sound);
	//free(sounds);
}

static void loadImages(void) {
	//Define assets to be loaded.
	AssetDef definitions[] = {

		{ "squid-01.png", false },
		{ "squid-02.png", false },

		{ "bug-01.png", false },
		{ "bug-02.png", false },
		{ "bug-03.png", false },
		{ "bug-04.png", false },
		{ "bug-05.png", false },
		{ "bug-06.png", false },

		{ "virus-01.png", false },
		{ "virus-02.png", false },
		{ "virus-03.png", false },
		{ "virus-04.png", false },
		{ "virus-05.png", false },
		{ "virus-06.png", false },

		{ "tux1-01.png", false },
		{ "tux1-02.png", false },
		{ "tux1-03.png", false },
		{ "tux1-jump.png", false },
		{ "tux1-jump2.png", false },

		{ "bg2.png", false },
		{ "tile-00.png", false },
		{ "tile-01.png", false },
		{ "tile-00b.png", false },
		{ "tile-01b.png", false },
		{ "tile-00c.png", false },
	};

	//Infer asset path from current directory.
	char* workingPath = SDL_GetBasePath();
	char assetsFolder[] = "data/";
	assetPath = combineStrings(workingPath, assetsFolder);

	//Allocate memory to Asset register.
	assetCount = sizeof(definitions) / sizeof(AssetDef);
	assets = malloc(sizeof(Asset) * assetCount);

	//Build and load each Asset into the register.
	for (int i = 0; i < assetCount; i++) {
		assets[i] = makeAsset(definitions[i]);
	}
}

static void loadSounds(void) {
	//const int SOUND_VOLUME = 128;

	//SoundDef defs[] = {
	//   //{ "pickup.wav", SOUND_VOLUME },
	//};

	//soundCount = sizeof(defs) / sizeof(SoundDef);
	//sounds = malloc(sizeof(SoundAsset) * soundCount);

	//for (int i = 0; i < soundCount; i++) {
	//	//Load music.
	//	char* path = combineStrings(assetPath, defs[i].filename);
	//	Mix_Chunk* chunk = Mix_LoadWAV(path);
	//	if (!chunk) fatalError("Could not find Asset on disk", path);

	//	//Reduce volume if called for.
	//	if (defs[i].volume < SDL_MIX_MAXVOLUME) Mix_VolumeChunk(chunk, defs[i].volume);

	//	//Add to register
	//	SoundAsset snd = {
	//		defs[i].filename,
	//		chunk
	//	};
	//	sounds[i] = snd;
	//}
}

void initAssets(void) {
	loadImages();
	loadSounds();
}

//void playOn(char* path, int channel) {
//	Mix_PlayChannel(channel, getSound(path).sound, 0);
//}
//
//void play(char* path) {
//	Mix_PlayChannel(-1, getSound(path).sound, 0);
//}
