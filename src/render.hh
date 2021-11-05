#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "level.hh"
#include "player.hh"
#include "vec2.hh"
#include "settings.hh"
using std::string;
using std::vector;

void renderLevel(SDL_Renderer* renderer, level &lvl, unordered_map <uint8_t, SDL_Texture*> &textures, string &gamepath, gplayer &player, vec2 &camera);
void renderText(SDL_Renderer* renderer, TTF_Font* font, gplayer player, settings_s settings);
void renderChat(SDL_Renderer* renderer, TTF_Font* font, vector <string> chat);