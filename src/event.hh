#include <SDL2/SDL.h>
#include "settings.hh"
#include "player.hh"
#include "level.hh"
#include "vec2.hh"

void handleEvent(SDL_Event& event, bool &run, const unsigned char* keyStates, settings_s &settings, gplayer &player, vec2 &camera, level &lvl, SDL_Window* window);