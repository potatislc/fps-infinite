#include <SDL_image.h>
#include <cstdio>
#include <string>
#include "ResourceLoader.h"
#include "App.h"

ResourceLoader::LoadedTextures ResourceLoader::loadedTextures;

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


void ResourceLoader::LoadedTextures::loadAll()
{
    playerMapIcon.set(loadTexture(TEXTURES_PATH"/map_icons/player.png"));
    testBg.set(loadTexture(TEXTURES_PATH"/backgrounds/gold-sky.png"));
    swarm.set(loadTexture(TEXTURES_PATH"/entities/swarm.png"));
    entityShadow.set(loadTexture(TEXTURES_PATH"/entities/entity-shadow.png"));

    testFloor.set(loadTextureStreaming(TEXTURES_PATH"/floors/test-floor.png"));
    quakeWater.set(loadTextureStreaming(TEXTURES_PATH"/floors/quake-water.png"));
}
