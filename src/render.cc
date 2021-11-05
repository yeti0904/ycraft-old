#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "level.hh"
#include "constants.hh"
#include "player.hh"
#include "vec2.hh"
#include "settings.hh"
using std::string;
using std::vector;
using std::to_string;

void rendertext(SDL_Renderer* renderer, TTF_Font* font, string text, size_t x, size_t y) {
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

void renderLevel(SDL_Renderer* renderer, level &lvl, unordered_map <uint8_t, SDL_Texture*> &textures, string &gamepath, gplayer &player, vec2 &camera) {
	SDL_Rect rect;
	string imgpath;
	SDL_Color colour = {0, 0, 0};
	rect.w = BLOCK_SIZE;
	rect.h = BLOCK_SIZE;

	// clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	uint16_t maxX;
	uint16_t maxY;
	maxX = camera.x + (SCR_X / BLOCK_SIZE);
	maxY = camera.y + (SCR_Y / BLOCK_SIZE);

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
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, gplayer player, settings_s settings) {
	string healthtext = "Health: " + to_string(player.health) + "%";
	string postext    = "Position: (" + to_string(player.x) + ", " + to_string(player.y) + ")";

	// render health text
	rendertext(renderer, font, healthtext, 10, SCR_Y - 10 - TEXT_SIZE);
	// render position text
	if (settings.showPosition) {
		rendertext(renderer, font, postext, 10, 10);
		if (settings.noclip) {
			rendertext(renderer, font, "Noclip ON", 10, 15 + TEXT_SIZE);
		}
	}
}

void renderChat(SDL_Renderer* renderer, TTF_Font* font, vector <string> chat) {
	// create background
	SDL_Rect rect;
	rect.x = 5;
	rect.y = SCR_Y - 40 - (5 * TEXT_SIZE);
	uint16_t longest = 0;
	for (uint8_t i = 0; i<5; ++i) {
		if (chat[chat.size()-1-i].length() > longest)
			longest = chat[chat.size()-1-i].length();
	}
	rect.w = ((longest * TEXT_SIZE) / 2) + 10;
	rect.h = 5 * TEXT_SIZE;

	// render
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(renderer, &rect);
	for (uint8_t i = 0; i<5; ++i) {
		rendertext(renderer, font, chat[chat.size()-1-i], 10, SCR_Y - 40 - TEXT_SIZE - (i*10));
	}
}