#include <string>
#include <cstdint>
#include <cmath>
#include <SDL2/SDL.h>
#include <libnoise/noise.h>
#include "level.hh"
using std::string;

void generateMap(level &lvl, uint16_t w, uint16_t h) {
	// perlin module
	noise::module::Perlin perlin;

	// set level properties
	lvl.w = w;
	lvl.h = h;

	double noise;

	// generate land features
    for (uint16_t i = 0; i<lvl.h; ++i) {
		for (uint16_t j = 0; j<lvl.w; ++j) {
			/*noise = (
				perlin.GetValue(j, i, 1.1)
				+ (0.5 *  perlin.GetValue(2 * j, 2 * i, 1.1))
				+ (0.25 *  perlin.GetValue(4 * j, 4 * i, 1.1))
			);
			noise = pow(noise, 0.15);*/
			noise = 0;
			//printf("%i, %i: %f\n", j, i, noise);
			if (noise < 0.7) {
				if (rand() % 10 != 1) lvl.backLoadAt(j, i, 6);
				else lvl.backLoadAt(j, i, 7);
			}
			else {
				lvl.backLoadAt(j, i, 8);
			}
		}
	}
	for (uint16_t i = 0; i<lvl.h; ++i) {
		for (uint16_t j = 0; j<lvl.w; ++j) {
			if (lvl.back_blocks[i][j].textureID != 8) {
				if (rand() % 40 == 1) lvl.frontLoadAt(j, i, 5);
			}
		}
	}
}