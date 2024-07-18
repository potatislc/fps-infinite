#pragma once
#include <SDL.h>

class Window
{
public:
    SDL_Window* sdlWindow;
    static int screenWidth;
    static int screenHeight;
    bool init();
};


