#pragma once
#include "SDL.h"

class Renderer
{
public:
    static SDL_Renderer* sdlRenderer;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
