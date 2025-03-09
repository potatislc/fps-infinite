#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "SDL_render.h"
#include "UniqueTexture.h"
#include "PixelArray.h"

#define TEXTURES_PATH RESOURCES_PATH"textures"

class ResourceLoader
{
public:
    class LoadedTextures
    {
    public:
        // Textures
        UniqueTexture testBg;
        UniqueTexture swarm;
        UniqueTexture testFloor;
        UniqueTexture entityShadow;
        UniqueTexture bullet;

        UniqueTexture uiCrosshair;

        void loadAll();
    };

    class LoadedPixelArrays
    {
    public:
        PixelArray<uint32_t> water;

        void loadAll();
    };

    static LoadedTextures loadedTextures;
    static LoadedPixelArrays loadedPixelArrays;
    static SDL_Texture* loadTexture(const std::string& path);
    static SDL_Texture* loadTextureStreaming(const std::string& path);
    static PixelArray<uint32_t> copyTextureToPixelArray(SDL_Texture* texture);
};