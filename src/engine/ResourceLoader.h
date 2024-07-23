#pragma once

#include <string>
#include "SDL_render.h"

#define TEXTURES_PATH RESOURCES_PATH"textures"

class ResourceLoader
{
public:
    static SDL_Texture* loadTexture(const std::string& path);
};