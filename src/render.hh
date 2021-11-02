#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "level.hh"
#include "player.hh"
#include "vec2.hh"
#include "settings.hh"
using std::string;

void renderLevel(SDL_Renderer* renderer, level &lvl, unordered_map <uint8_t, SDL_Texture*> &textures, string &gamepath, gplayer &player, TTF_Font* font, vec2 &camera, settings_s settings);