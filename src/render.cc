#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "level.hh"
#include "constants.hh"
#include "player.hh"
#include "vec2.hh"
#include "settings.hh"
using std::string;
using std::to_string;

void renderText(SDL_Renderer* renderer, TTF_Font* font, string text, size_t x, size_t y) {
	SDL_Rect rect;
	SDL_Color colour = {0, 0, 0};
	SDL_Surface* textsurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	SDL_Texture* texttexture = SDL_CreateTextureFromSurface(renderer, textsurface);
	rect.x = x+1;
	rect.y = y+1;
	rect.h = TEXT_SIZE;
	rect.w = (text.length() * TEXT_SIZE) / 2;
	SDL_RenderCopy(renderer, texttexture, NULL, &rect);
	rect.x -= 1;
	rect.y -= 1;
	colour = {255, 255, 255};
	textsurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	texttexture = SDL_CreateTextureFromSurface(renderer, textsurface);
	SDL_RenderCopy(renderer, texttexture, NULL, &rect);
	SDL_DestroyTexture(texttexture);
	SDL_FreeSurface(textsurface);
}

void renderLevel(SDL_Renderer* renderer, level &lvl, unordered_map <uint8_t, SDL_Texture*> &textures, string &gamepath, gplayer &player, TTF_Font* font, vec2 &camera, settings_s settings) {
	SDL_Rect rect;
	string imgpath;
	string healthtext = "Health: " + to_string(player.health) + "%";
	string postext    = "Position: (" + to_string(player.x) + ", " + to_string(player.y) + ")";
	SDL_Color colour = {0, 0, 0};
	SDL_Surface* textsurface;
	SDL_Texture* texttexture;
	rect.w = BLOCK_SIZE;
	rect.h = BLOCK_SIZE;

	// clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	uint16_t maxX;
	uint16_t maxY;
	maxX = camera.x + (320 / BLOCK_SIZE);
	maxY = camera.y + (240 / BLOCK_SIZE);

	// handle back layer
	for (int16_t i = camera.y; i<maxY; ++i) {
		for (int16_t j = camera.x; j<maxX; ++j) {
			rect.x = (j - camera.x) * BLOCK_SIZE;
			rect.y = (i - camera.y) * BLOCK_SIZE;
			SDL_RenderCopy(renderer, textures[lvl.back_blocks[i][j].textureID], NULL, &rect);
		}
	}

	// handle front layer
	for (int16_t i = camera.y; i<maxY; ++i) {
		for (int16_t j = camera.x; j<maxX; ++j) {
			rect.x = (j - camera.x) * BLOCK_SIZE;
			rect.y = (i - camera.y) * BLOCK_SIZE;
			if (lvl.front_blocks[i][j].textureID != 0) 
				SDL_RenderCopy(renderer, textures[lvl.front_blocks[i][j].textureID], NULL, &rect);
		}
	}

	// render player
	rect.x = (player.x - camera.x) * BLOCK_SIZE;
	rect.y = (player.y - camera.y) * BLOCK_SIZE;
	SDL_RenderCopy(renderer, player.texture, NULL, &rect);

	// render health text
	renderText(renderer, font, healthtext, 10, 220);
	// render position text
	if (settings.showPosition) {
		renderText(renderer, font, postext, 10, 10);
	}

	// finished rendering
	SDL_RenderPresent(renderer);
}