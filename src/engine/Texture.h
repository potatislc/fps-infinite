#pragma once

#include <string>
#include <SDL.h>

class Texture
{
public:
    SDL_Texture* sdlTexture;
    void set(SDL_Texture* texture);
    ~Texture();
}; // A simple wrapper class for SDL_Texture