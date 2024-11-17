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
        UniqueTexture playerMapIcon;
        UniqueTexture testBg;

        void loadAll();
    };

    static LoadedTextures loadedTextures;
    static SDL_Texture* loadTexture(const std::string& path);
};