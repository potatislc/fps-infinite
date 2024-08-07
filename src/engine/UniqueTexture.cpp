#include "UniqueTexture.h"
#include "ResourceLoader.h"


void UniqueTexture::destroyTexture()
{
    if (sdlTexture != nullptr) SDL_DestroyTexture(sdlTexture);
}

void UniqueTexture::set(SDL_Texture *texture)
{
    destroyTexture();
    sdlTexture = texture;
}

UniqueTexture::~UniqueTexture()
{
    destroyTexture();
}

SDL_Texture *UniqueTexture::get() const
{
    return sdlTexture;
}