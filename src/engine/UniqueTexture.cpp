#include "UniqueTexture.h"
#include "ResourceLoader.h"
#include <SDL_render.h>


void UniqueTexture::destroyTexture()
{
    if (sdlTexture != nullptr) SDL_DestroyTexture(sdlTexture);
}

void UniqueTexture::set(SDL_Texture *texture)
{
    destroyTexture();
    updateSize(texture);
    sdlTexture = texture;
}

UniqueTexture::~UniqueTexture()
{
    destroyTexture();
}

SDL_Texture* UniqueTexture::get()
{
    return sdlTexture;
}

Utils::Vector2I UniqueTexture::getSize()
{
    return size;
}

UniqueTexture::UniqueTexture(SDL_Texture *texture) : sdlTexture(texture)
{
    updateSize(texture);
}

void UniqueTexture::updateSize(SDL_Texture *texture)
{
    if (texture != nullptr)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    }
    else
    {
        size = {0, 0};
    }
}
