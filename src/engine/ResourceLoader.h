#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "SDL_render.h"
#include "UniqueTexture.h"

#define TEXTURES_PATH RESOURCES_PATH"textures"

class ResourceLoader
{
public:
    class LoadedTextures
    {
    public:
        // Map Icons
        UniqueTexture playerMapIcon;

        void loadAll();
    };

    static LoadedTextures loadedTextures;
    static SDL_Texture* loadTexture(const std::string& path);
};