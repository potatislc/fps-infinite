#include "Texture.h"
#include "ResourceLoader.h"

void Texture::set(SDL_Texture *texture)
{
    sdlTexture = texture;
}

Texture::~Texture()
{
    if (sdlTexture != nullptr) SDL_DestroyTexture(sdlTexture);
}