#pragma once
#include <SDL.h>

extern SDL_Renderer* currentRenderer;

class Renderer
{
public:
    SDL_Renderer* sdlRenderer;
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
