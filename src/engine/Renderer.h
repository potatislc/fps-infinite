#pragma once
#include "SDL2/SDL.h"

class Renderer
{
public:
    static SDL_Renderer* sdlRenderer;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
