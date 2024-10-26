#include "UniqueTexture.h"
#include "ResourceLoader.h"
#include <SDL_render.h>


void UniqueTexture::destroyTexture()
{
    if (sdlTexture) SDL_DestroyTexture(sdlTexture);
}

void UniqueTexture::set(SDL_Texture *texture)
{
    destroyTexture();
    sdlTexture = texture;
    updateSize(texture);
}

UniqueTexture::~UniqueTexture()
{
    destroyTexture();
}

SDL_Texture* UniqueTexture::get()
{
    return sdlTexture;
}

SDL_Rect* UniqueTexture::getRect()
{
    return &rect;
}

UniqueTexture::UniqueTexture(SDL_Texture *texture) : sdlTexture(texture)
{
    updateSize(texture);
}

void UniqueTexture::updateSize(SDL_Texture *texture)
{
    if (texture != nullptr)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    }
    else
    {
        rect = {0, 0, 0, 0};
    }
}
