#pragma once

#include <string>
#include <SDL.h>

class UniqueTexture
{
    SDL_Texture* sdlTexture;
    inline void destroyTexture();
public:
    explicit UniqueTexture(SDL_Texture* texture = nullptr) : sdlTexture(texture) {};
    void set(SDL_Texture* texture);
    SDL_Texture* get() const;
    ~UniqueTexture();
}; // A simple wrapper class for SDL_Texture