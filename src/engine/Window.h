#pragma once
#include "SDL.h"

class Window
{
public:
    SDL_Window* sdlWindow = nullptr;
    uint16_t width;
    uint16_t height;
    uint16_t centerW;
    uint16_t centerH;

    Window();
    ~Window();
    bool init();
};


