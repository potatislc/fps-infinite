#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class MessageTexture
{
    static SDL_Texture* Create(SDL_Renderer* renderer, TTF_Font* font, const char* message, SDL_Color color);
};
