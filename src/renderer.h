#pragma once
#include <SDL.h>

class Renderer
{
    void drawWorld() const;
    void drawUi() const;

public:
    SDL_Renderer* sdlRenderer;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
