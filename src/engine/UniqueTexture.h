#pragma once

#include <string>
#include <SDL.h>

class UniqueTexture
{
    SDL_Texture* sdlTexture;
    inline void destroyTexture();
public:
    void set(SDL_Texture* texture);
    SDL_Texture* get() const;
    ~UniqueTexture();
}; // A simple wrapper class for SDL_Texture