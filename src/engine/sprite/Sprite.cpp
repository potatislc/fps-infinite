#include "Sprite.h"

Sprite::Sprite(UniqueTexture& texture, int frameCount, float animSpeed, int startingFrame = 0) :
    texture(texture), frameCount(frameCount), frame(startingFrame), animSpeed(animSpeed)
{
    animProgress = static_cast<float>(startingFrame) / static_cast<float>(frameCount);
    SDL_Rect rect = *texture.getRect();
    subRect = SDL_Rect{0, 0, rect.w, rect.h / frameCount};
}

void Sprite::animate(float delta)
{
    animProgress += animSpeed * delta;
    if (animProgress > 1) animProgress = 0;
    if (animProgress < 0) animProgress = 1;

    frame = static_cast<int>(animProgress * static_cast<float>(frameCount));
}

void Sprite::draw(SDL_Renderer* renderer, const SDL_Rect& dst)
{
    SDL_RenderCopy(renderer, texture.get(), &subRect, &dst);
}


