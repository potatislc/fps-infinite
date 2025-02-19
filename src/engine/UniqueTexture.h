#pragma once

#include <string>
#include <SDL.h>
#include "engine/utils/Utils.h"

class UniqueTexture
{
    SDL_Texture* sdlTexture;
    SDL_Rect rect = {0, 0, 0, 0};
    inline void destroyTexture();
    inline void updateSize(SDL_Texture *texture);
public:
    explicit UniqueTexture(SDL_Texture* texture = nullptr);
    void set(SDL_Texture* texture);

    SDL_Texture* get();
    SDL_Rect* getRect();
    ~UniqueTexture();
}; // A simple wrapper class for SDL_Texture