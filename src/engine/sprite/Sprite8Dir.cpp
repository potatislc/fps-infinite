#include "Sprite8Dir.h"

Sprite8Dir::Sprite8Dir(UniqueTexture& texture, int frameCount, float animSpeed, int startingFrame) :
    Sprite(texture, frameCount, animSpeed, startingFrame)
{

}

void Sprite8Dir::draw(SDL_Renderer* renderer, SDL_Rect dst, uint8_t dir)
{

}
