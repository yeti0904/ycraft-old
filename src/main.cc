#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "render.hh"
#include "level.hh"
#include "constants.hh"
#include "player.hh"
#include "util.hh"
#include "vec2.hh"
#include "generator.hh"
#include "settings.hh"
#include "event.hh"
using std::string;
using std::to_string;

#ifdef _WIN32
int WinMain(int argc, char** argv) {
#else
int main(int argc, char** argv) {
#endif
	string gamepath = argv[0];
	gamepath = gamepath.substr(0, gamepath.rfind('/'));
	uint32_t coins = 0;

	/*printf("Checking for game files...\n");
	if (gamefilesExist(gamepath).size() == 0) {
		printf("Game files exist\n");
	}
	else {
		printf("Missing game files:\n");
		for (size_t i = 0; i<gamefilesExist(gamepath).size(); ++i) {
			printf("%s\n", gamefilesExist(gamepath)[i].c_str());
		}
		return 1;
	}*/
	printf("Starting video...\n");
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { // initialize SDL2
		printf("Video initialization error: %s\n", SDL_GetError());
	}
	string winTitle = "ycraft";
	SDL_Window* window = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		printf("Failed to create window: %s\n", SDL_GetError());
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event event;

	// create font
	TTF_Font* font = TTF_OpenFont(string(gamepath + "/font.ttf").c_str(), TEXT_SIZE);

	bool run = true;
	const unsigned char* keyStates;
	gplayer player;
	printf("Started\n");

	// hacks
	settings_s settings;
	settings.noclip       = false;
	settings.showPosition = true;
	settings.showChat     = false;

	// chat
	vector <string> chat = {"", "", "", "", ""};
	chat.push_back("Welcome to ycraft");

	// config
	SDL_RenderSetLogicalSize(renderer, SCR_X, SCR_Y);
	printf("Set resolution to %ix%i\n", SCR_X, SCR_Y);

	// window icon
	SDL_Surface* icon;
	icon = IMG_Load(string(gamepath + "/icon.png").c_str());
	SDL_SetWindowIcon(window, icon);
	printf("Set icon to %s\n", string(gamepath + "/icon.png").c_str());

	// load textures
	printf("Loading textures..\n");
	const uint8_t textureCount = 8;
	unordered_map <uint8_t, SDL_Texture*> textures;
	SDL_Surface* tmpSurface;
	for (uint8_t i  = 1; i<=textureCount; ++i) {
		tmpSurface  = IMG_Load(string(gamepath + "/textures/" + to_string(i) + ".png").c_str());
		textures[i] = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}

	// create player
	player.x       = round((SCR_X / BLOCK_SIZE) / 2);
	player.y       = round((SCR_Y / BLOCK_SIZE) / 2);
	player.health  = 100;
	player.surface = IMG_Load(string(gamepath + "/textures/player.png").c_str());
	player.texture = SDL_CreateTextureFromSurface(renderer, player.surface);
	printf("Loaded player\n");
	printf("Spawn point: %i, %i\n", player.x, player.y);

	// create camera
	vec2 camera;
	camera.x = 0;
	camera.y = 0;
	printf("Created camera\n");

	// generate level
	printf("Generating world..\n");
	level lvl;
	vec2  lvlSize = {128, 128};
	generateMap(lvl, lvlSize.x, lvlSize.y);
	
	printf("Loaded level\n");

	while (run) {
		// event
		handleEvent(event, run, keyStates, settings, player, camera, lvl, window);

		renderLevel(renderer, lvl, textures, gamepath, player, camera);
		renderText(renderer, font, player, settings);
		if (settings.showChat) {
			renderChat(renderer, font, chat);
		}
		SDL_RenderPresent(renderer);
	}


	// free resources
	for (uint8_t i = 0; i<textureCount; ++i) {
		SDL_DestroyTexture(textures[i]);
	}
	SDL_DestroyTexture(player.texture);
	SDL_FreeSurface(player.surface);
	SDL_FreeSurface(icon);

	printf("\rExiting\n");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	return 0;
}
