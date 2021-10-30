#include <string>
#include <SDL2/SDL.h>
#include "level.hh"
#include "player.hh"
#include "vec2.hh"
using std::string;

void render(SDL_Renderer* renderer, level lvl, string gamepath, gplayer player, TTF_Font* font, uint32_t coins, vec2 camera);