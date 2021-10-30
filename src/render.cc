#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "level.hh"
#include "constants.hh"
#include "player.hh"
#include "vec2.hh"
using std::string;
using std::to_string;

void render(SDL_Renderer* renderer, level lvl, string gamepath, gplayer player, TTF_Font* font, uint32_t coins, vec2 camera) {
	SDL_Rect rect;
	string imgpath;
	string cointext = "Coins: " + to_string(coins);
	SDL_Color colour = {0, 0, 0};
	SDL_Surface* coinsurface;
	SDL_Texture* cointexture;
	rect.w = BLOCK_SIZE;
	rect.h = BLOCK_SIZE;

	// clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// handle back layer
	for (int16_t i = camera.y; i<lvl.h; ++i) {
		for (int16_t j = camera.x; j<lvl.w; ++j) {
			// get texture
			imgpath = gamepath + "/textures/" + to_string(lvl.back_blocks[i][j].textureID) + ".png";
			// render it
			rect.x = (j - camera.x) * BLOCK_SIZE;
			rect.y = (i - camera.y) * BLOCK_SIZE;
			SDL_RenderCopy(renderer, lvl.back_blocks[i][j].texture, NULL, &rect);
		}
	}

	// handle front layer
	for (int16_t i = camera.y; i<lvl.h; ++i) {
		for (int16_t j = camera.x; j<lvl.w; ++j) {
			// get texture
			imgpath = gamepath + "/textures/" + to_string(lvl.front_blocks[i][j].textureID) + ".png";
			// render it
			rect.x = (j - camera.x) * BLOCK_SIZE;
			rect.y = (i - camera.y) * BLOCK_SIZE;
			if (lvl.front_blocks[i][j].textureID != 0) SDL_RenderCopy(renderer, lvl.front_blocks[i][j].texture, NULL, &rect);
		}
	}

	// render player
	rect.x = (player.x - camera.x) * BLOCK_SIZE;
	rect.y = (player.y - camera.y) * BLOCK_SIZE;
	SDL_RenderCopy(renderer, player.texture, NULL, &rect);

	// render text
	coinsurface = TTF_RenderText_Solid(font, cointext.c_str(), colour);
	cointexture = SDL_CreateTextureFromSurface(renderer, coinsurface);
	rect.x = 10;
	rect.y = 220;
	rect.h = TEXT_SIZE;
	rect.w = (cointext.length() * TEXT_SIZE) / 2;
	SDL_RenderCopy(renderer, cointexture, NULL, &rect);
	rect.x -= 1;
	rect.y -= 1;
	colour = {255, 255, 255};
	coinsurface = TTF_RenderText_Solid(font, cointext.c_str(), colour);
	cointexture = SDL_CreateTextureFromSurface(renderer, coinsurface);
	SDL_RenderCopy(renderer, cointexture, NULL, &rect);

	SDL_DestroyTexture(cointexture);
	SDL_FreeSurface(coinsurface);

	// finished rendering
	SDL_RenderPresent(renderer);
}