#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include "level.hh"
using std::string;

void generateMap(level &lvl, uint16_t w, uint16_t h, string gamepath, SDL_Renderer* renderer) {
	// set level properties
	lvl.w = w;
	lvl.h = h;

	// generate land features
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
}