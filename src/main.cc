#include <cstdio>
#include <cstdlib>
#include <cstring>
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
	SDL_Init(SDL_INIT_VIDEO); // initialize SDL2
	string winTitle = "coingame";
	SDL_Window* window = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event event;
	// create font
	TTF_Font* font = TTF_OpenFont(string(gamepath + "/font.ttf").c_str(), TEXT_SIZE);
	bool run = true;
	const unsigned char* keyStates;
	gplayer player;
	printf("Started\n");

	// config
	SDL_RenderSetLogicalSize(renderer, 320, 240);
	printf("Set resolution to 320x240\n");

	// window icon
	SDL_Surface* icon;
	icon = IMG_Load(string(gamepath + "/icon.png").c_str());
	SDL_SetWindowIcon(window, icon);
	printf("Set icon to %s\n", string(gamepath + "/icon.png").c_str());

	// create player
	player.x = 10;
	player.y = 7;
	player.surface = IMG_Load(string(gamepath + "/textures/player.png").c_str());
	player.texture = SDL_CreateTextureFromSurface(renderer, player.surface);
	printf("Loaded player\n");

	// create camera
	vec2 camera;
	camera.x = 0;
	camera.y = 0;
	printf("Created camera\n");

	// generate level
	level lvl;
	lvl.w = 50;
	lvl.h = 50;
	for (uint16_t i = 0; i<lvl.h; ++i) {
        for (uint16_t j = 0; j<lvl.w; ++j) {
			if (rand() % 10 != 1) lvl.backLoadAt(renderer, j, i, 6, gamepath);
			else lvl.backLoadAt(renderer, j, i, 7, gamepath);
		}
	}
	for (uint16_t i = 0; i<lvl.h; ++i) {
        for (uint16_t j = 0; j<lvl.w; ++j) {
			if (rand() % 20 == 1) lvl.frontLoadAt(renderer, j, i, 5, gamepath);
		}
	}
	
	printf("Loaded level\n");

	while (run) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					run = false;
					break;
				}
				case SDL_KEYDOWN: {
					bool playerMoved = false;
					keyStates = SDL_GetKeyboardState(NULL);
					if (keyStates[SDL_SCANCODE_W]) {
						if ((!lvl.front_blocks[player.y-1][player.x].collision)
						&& (player.y != 0)) {
							playerMoved = true;
							-- player.y;
							-- camera.y;
						}
					}
					if (keyStates[SDL_SCANCODE_A]) {
						if ((!lvl.front_blocks[player.y][player.x-1].collision)
						&& (player.x != 0)) {							
							playerMoved = true;
							-- player.x;
							-- camera.x;
						}
					}
					if (keyStates[SDL_SCANCODE_S]) {
						if ((!lvl.front_blocks[player.y+1][player.x].collision)
						&& (player.y != lvl.h-1)) {
							playerMoved = true;
							++ player.y;
							++ camera.y;
						}
					}
					if (keyStates[SDL_SCANCODE_D]) {
						if ((!lvl.front_blocks[player.y][player.x+1].collision)
						&& (player.x != lvl.w-1)) {
							playerMoved = true;
							++ player.x;
							++ camera.x;
						}
					}

					if (playerMoved) {
						if ((lvl.front_blocks[player.y][player.x].textureID != 0) && (lvl.front_blocks[player.y][player.x].collectible)) {
							coins += lvl.front_blocks[player.y][player.x].collectAmount;
							printf("Gained %u coins\n", lvl.front_blocks[player.y][player.x].collectAmount);
							lvl.frontLoadAt(renderer, player.x, player.y, 0, gamepath);
						}
					}
					break;
				}
			}
		}
		render(renderer, lvl, gamepath, player, font, coins, camera);

		// fps limiter
		SDL_Delay(1000/ MAX_FPS);
	}
	// free resources
	for (uint16_t i = 0; i<lvl.h; ++i) {
		for (uint16_t j = 0; j<lvl.w; ++j) {
			SDL_DestroyTexture(lvl.back_blocks[i][j].texture);
			SDL_FreeSurface(lvl.back_blocks[i][j].surface);
		}
	}
	for (uint16_t i = 0; i<lvl.h; ++i) {
		for (uint16_t j = 0; j<lvl.w; ++j) {
			SDL_DestroyTexture(lvl.front_blocks[i][j].texture);
			SDL_FreeSurface(lvl.front_blocks[i][j].surface);
		}
	}
	SDL_DestroyTexture(player.texture);
	SDL_FreeSurface(player.surface);
	SDL_FreeSurface(icon);

	printf("Exiting\n");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	SDL_Quit();
	TTF_Quit();
	return 0;
}