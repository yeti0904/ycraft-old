#include <SDL2/SDL.h>
#include "constants.hh"
#include "settings.hh"
#include "player.hh"
#include "level.hh"
#include "vec2.hh"

void handleEvent(SDL_Event& event, bool &run, const unsigned char* keyStates, settings_s &settings, gplayer &player, vec2 &camera, level &lvl, SDL_Window* window) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				run = false;
				break;
			}
			case SDL_KEYDOWN: {
				// movement
				bool playerMoved = false;
				bool canMove     = true;
				if (!settings.noclip) {
					if (lvl.front_blocks[player.y-1][player.x].collision)
						canMove = false;
				}

				keyStates = SDL_GetKeyboardState(NULL);
				if (keyStates[SDL_SCANCODE_W]) {
					if (((!lvl.front_blocks[player.y-1][player.x].collision)
					&& (player.y != 0))
					|| settings.noclip) {
						playerMoved = true;
						-- player.y;
						-- camera.y;
					}
				}
				if (keyStates[SDL_SCANCODE_A]) {
					if (((!lvl.front_blocks[player.y][player.x-1].collision)
					&& (player.x != 0))
					|| settings.noclip) {							
						playerMoved = true;
						-- player.x;
						-- camera.x;
					}
				}
				if (keyStates[SDL_SCANCODE_S]) {
					if (((!lvl.front_blocks[player.y+1][player.x].collision)
					&& (player.y != lvl.h-1))
					|| settings.noclip) {
						playerMoved = true;
						++ player.y;
						++ camera.y;
					}
				}
				if (keyStates[SDL_SCANCODE_D]) {
					if (((!lvl.front_blocks[player.y][player.x+1].collision)
					&& (player.x != lvl.w-1))
					|| settings.noclip) {
						playerMoved = true;
						++ player.x;
						++ camera.x;
					}
				}
				// hax
				if (keyStates[SDL_SCANCODE_X]) {
					settings.noclip = !settings.noclip;
				}
				if (keyStates[SDL_SCANCODE_F3]) {
					settings.showPosition = !settings.showPosition;
				}
				// chat
				if (keyStates[SDL_SCANCODE_T]) {
					settings.showChat = !settings.showChat;
				}

				// rendering options
				if (keyStates[SDL_SCANCODE_F11]) { // fullscreen
					uint32_t fullscreenFlag = SDL_WINDOW_FULLSCREEN;
   					bool isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
    				SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
    				SDL_ShowCursor(isFullscreen);
				}

				break;
			}
		}
	}
}