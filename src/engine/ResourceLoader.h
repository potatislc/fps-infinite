#pragma once

#include <string>
#include "SDL_render.h"

class ResourceLoader
{
    static SDL_Texture* loadTexture(const std::string& path);
};