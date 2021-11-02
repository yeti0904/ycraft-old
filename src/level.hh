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
		back_blocks[y][x].textureID = textureID;
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
				// rock
				front_blocks[y][x].collision     = true;
				break;
			}
		}

		front_blocks[y][x].textureID = textureID;
	}
};