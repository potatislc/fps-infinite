#pragma once

#include "Sprite.h"

class Sprite8Dir : public Sprite
{
public:
    Sprite8Dir(UniqueTexture& texture, int frameCount, float animSpeed, int startingFrame);
    void draw(SDL_Renderer* renderer, SDL_Rect dst, uint8_t dir);
};