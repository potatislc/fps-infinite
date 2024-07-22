#pragma once
#include "SDL.h"

class Renderer
{
public:
    static SDL_Renderer* sdlRenderer;
    static SDL_Rect viewport;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
