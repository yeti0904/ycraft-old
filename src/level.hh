#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>
using std::unordered_map;
using std::string;
using std::to_string;

struct block {
	uint8_t textureID;
	SDL_Surface* surface;
	SDL_Texture* texture;
	bool collision;
	bool deadly;
	bool collectible;
	uint8_t collectAmount;
};

class level {
	public:
	level() {}
	uint16_t w, h;
	unordered_map <uint16_t, unordered_map <uint16_t, block>> back_blocks;
	unordered_map <uint16_t, unordered_map <uint16_t, block>> front_blocks;

	void backLoadAt(SDL_Renderer* renderer, uint16_t x, uint16_t y, uint8_t textureID, string gamepath) {
		string imgpath;
		imgpath = gamepath + "/textures/" + to_string(textureID) + ".png";
		back_blocks[y][x].surface = IMG_Load(imgpath.c_str());
		back_blocks[y][x].texture = SDL_CreateTextureFromSurface(renderer, back_blocks[y][x].surface);
	}

	void frontLoadAt(SDL_Renderer* renderer, uint16_t x, uint16_t y, uint8_t textureID, string gamepath) {
		string imgpath;
		imgpath = gamepath + "/textures/" + to_string(textureID) + ".png";
		// block properties
		switch (textureID) {
			case 1: {
				// brick
				front_blocks[y][x].collision = true;
				break;
			}
			case 2: {
				// stone
				front_blocks[y][x].collision = true;
				break;
			}
			case 3: {
				// wood
				front_blocks[y][x].collision = true;
				break;
			}
			case 4: {
				// table
				front_blocks[y][x].collision = true;
				break;
			}
			case 5: {
				// moneybag
				front_blocks[y][x].collision     = false;
				front_blocks[y][x].collectible   = true;
				front_blocks[y][x].collectAmount = 100;
				break;
			}
		}

		front_blocks[y][x].textureID = textureID;
		if (textureID != 0) {
			front_blocks[y][x].surface = IMG_Load(imgpath.c_str());
			front_blocks[y][x].texture = SDL_CreateTextureFromSurface(renderer, front_blocks[y][x].surface);
		}
	}
};