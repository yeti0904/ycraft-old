#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

struct gplayer {
    SDL_Surface* surface;
    SDL_Texture* texture;
    uint16_t x, y;
};