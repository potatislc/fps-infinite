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

void ResourceLoader::LoadedTextures::loadAll()
{
    playerMapIcon.set(loadTexture(TEXTURES_PATH"/map_icons/player.png"));
    testBg.set(loadTexture(TEXTURES_PATH"/backgrounds/test-bg.png"));
    swarm.set(loadTexture(TEXTURES_PATH"/entities/swarm.png"));
    testFloor.set(loadTexture(TEXTURES_PATH"/floors/test-floor.png"));
}
