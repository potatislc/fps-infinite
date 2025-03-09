#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <cstring>
#include "ResourceLoader.h"
#include "App.h"

ResourceLoader::LoadedTextures ResourceLoader::loadedTextures;
ResourceLoader::LoadedPixelArrays ResourceLoader::loadedPixelArrays;

SDL_Texture *ResourceLoader::loadTexture(const std::string& path)
{
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(App::renderer.sdlRenderer, loadedSurface);
        if( newTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Texture* ResourceLoader::loadTextureStreaming(const std::string& path)
{
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create a streaming texture
        newTexture = SDL_CreateTexture(
                App::renderer.sdlRenderer,
                SDL_PIXELFORMAT_RGBA8888, // Choose an appropriate pixel format
                SDL_TEXTUREACCESS_STREAMING,
                loadedSurface->w,
                loadedSurface->h
        );

        if (newTexture == nullptr)
        {
            printf("Unable to create streaming texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Lock the texture to copy pixel data
            void* pixels;
            int pitch;
            if (SDL_LockTexture(newTexture, nullptr, &pixels, &pitch) == 0)
            {
                memcpy(pixels, loadedSurface->pixels, loadedSurface->pitch * loadedSurface->h);
                SDL_UnlockTexture(newTexture);
            }
            else
            {
                printf("Unable to lock texture for %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
                SDL_DestroyTexture(newTexture);
                newTexture = nullptr;
            }
        }

        // Get rid of the loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

PixelArray<uint32_t> ResourceLoader::copyTextureToPixelArray(SDL_Texture* texture)
{
    if (!texture)
    {
        throw std::invalid_argument("Texture is null");
    }

    uint32_t format;
    int width, height;
    if (SDL_QueryTexture(texture, &format, nullptr, &width, &height) != 0)
    {
        throw std::runtime_error(std::string("SDL_QueryTexture failed: ") + SDL_GetError());
    }

    if (format != SDL_PIXELFORMAT_RGBA8888)
    {
        throw std::invalid_argument("Texture is not in RGBA8888 format");
    }

    uint32_t* pixels;
    int pitch;
    if (SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch) != 0) {
        throw std::runtime_error(std::string("SDL_LockTexture failed: ") + SDL_GetError());
    }

    PixelArray<uint32_t> pixelArray = PixelArray<uint32_t>(new uint32_t[width * height], width, height);

    for (int y = 0; y < height; ++y) {
        std::memcpy(
                &pixelArray.pixels[y * width],
                reinterpret_cast<uint8_t*>(pixels) + y * pitch,
                width * sizeof(uint32_t)
        );
    }

    SDL_UnlockTexture(texture);

    return pixelArray;
}

void ResourceLoader::LoadedTextures::loadAll()
{
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    testBg.set(loadTexture(TEXTURES_PATH"/backgrounds/flat-lite.png"));
    swarm.set(loadTexture(TEXTURES_PATH"/entities/swarm.png"));
    entityShadow.set(loadTexture(TEXTURES_PATH"/entities/entity-shadow-small.png"));
    bullet.set(loadTexture(TEXTURES_PATH"/entities/bullet.png"));
    uiCrosshair.set(loadTexture(TEXTURES_PATH"/ui/crosshair.png"));

    testFloor.set(loadTextureStreaming(TEXTURES_PATH"/floors/test-floor.png"));

}

void ResourceLoader::LoadedPixelArrays::loadAll()
{
    UniqueTexture quakeWater = UniqueTexture(loadTextureStreaming(TEXTURES_PATH"/floors/quake-water.png"));

    water = copyTextureToPixelArray(quakeWater.get());
}
