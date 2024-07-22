#pragma once
#include "SDL.h"

class Window
{
public:
    SDL_Window* sdlWindow;
    static uint16_t width;
    static uint16_t height;
    static uint16_t centerW;
    static uint16_t centerH;
    bool init();
};


