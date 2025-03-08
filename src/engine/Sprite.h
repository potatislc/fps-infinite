#pragma once

#include "engine/utils/Utils.h"
#include "UniqueTexture.h"

class Sprite
{
public:
    UniqueTexture& texture;
    int frame;
    int frameCount;
    float animSpeed;
    float animProgress = 0;
    SDL_Rect subRect;

    Sprite(UniqueTexture& texture, int frameCount, float animSpeed, int startingFrame);
    void animate(float delta);
};
