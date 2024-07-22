#pragma once
#include "SDL.h"

class Renderer
{
public:
    SDL_Renderer* sdlRenderer;
    SDL_Rect viewport;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
