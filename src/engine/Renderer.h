#pragma once
#include <utility>
#include "SDL.h"

class Renderer
{
public:
    SDL_Renderer* sdlRenderer;
    SDL_Rect viewport;
    const std::pair<uint16_t, uint16_t> viewportDefaultSize = { 512, 512 };
    bool init(SDL_Window* sdlWindow);
    void render() const;
};
