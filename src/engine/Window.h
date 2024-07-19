#pragma once
#include "SDL2/SDL.h"

class Window
{
public:
    SDL_Window* sdlWindow;
    static int screenWidth;
    static int screenHeight;
    bool init();
};


