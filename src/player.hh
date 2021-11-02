#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

struct gplayer {
    SDL_Surface* surface; // used for rendering
    SDL_Texture* texture; // also used for rendering
    uint16_t     x, y;    // position
    uint8_t      health;  // percentage
};