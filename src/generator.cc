#include <string>
#include <cstdint>
#include <cmath>
#include <SDL2/SDL.h>
#include <noise/noise.h>
#include "level.hh"
using std::string;
#define lerp(a,b,w) a*(1-w)+b*w

double integerNoise (int n) {
  n = (n >> 13) ^ n;
  int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
  return 1.0 - ((double)nn / 1073741824.0);
}

double interpolateNoise(double x) {
  int intX = (int)(floor (x));
  double n0 = integerNoise(intX);
  double n1 = integerNoise(intX + 1);
  double weight = x - floor(x);
  double noise = lerp(n0, n1, weight);
  return noise;
}

void generateMap(level &lvl, uint16_t w, uint16_t h) {
	// set level properties
	lvl.w = w;
	lvl.h = h;

	noise::module::Perlin perlin;
	double noise = 0.5;

	// generate land features
    for (uint16_t i = 0; i<lvl.h; ++i) {
		for (uint16_t j = 0; j<lvl.w; ++j) {
			/*noise = perlin.GetValue(j + 0.5, i + 0.5, 5.5);
			noise = interpolateNoise(noise);*/
			noise = 0.6;
			if (noise > 0.5) {
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
