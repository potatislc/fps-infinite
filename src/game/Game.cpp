#include <iostream>
#include "Game.h"
#include "engine/InputMap.h"
#include "Player.h"
#include "engine/ResourceLoader.h"
#include "engine/App.h"

std::shared_ptr<Player> Game::currentPlayer = std::make_shared<Player>((glm::vec3){0, 0, 0}, 0, 1);
Renderer::ViewPortCamera Game::mapCamera = Renderer::ViewPortCamera((SDL_Rect){0, 0, 427, 240});
Camera3D Game::camera3D = Camera3D(90);

Game::Game()
{
    InputMap::addKeyBinding("Quit", SDLK_ESCAPE);
    InputMap::addKeyBinding("Left", SDLK_a);
    InputMap::addKeyBinding("Right", SDLK_d);
    InputMap::addKeyBinding("Up", SDLK_w);
    InputMap::addKeyBinding("Down", SDLK_s);
}

void Game::start()
{
    ResourceLoader::loadedTextures.loadAll();
    mapCamera.setRenderTarget(App::renderer.sdlRenderer);
    world.addChild(currentPlayer);
    // world.addChild(std::make_shared<Player>((glm::vec3){5, 0, 6}, 0, 1)); Test
}

void Game::update()
{
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED) exit(0);
    world.update();
}

void Game::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 50, 0, 175, 255);
    SDL_Rect rect = {0, 0, App::renderer.viewport.w, App::renderer.viewport.h};
    SDL_RenderFillRect(renderer, &rect);
    world.draw(renderer);
    camera3D.drawFov(renderer);
    drawMapEntities(renderer, world);
}

void Game::drawMapEntities(SDL_Renderer* renderer, const EntityScene& entityScene)
{

    SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, mapRect.w, mapRect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000); // GetWindowSurface also

    SDL_LockSurface(mapSurface);
    {
        auto* pixels = (uint32_t*)mapSurface->pixels;
        uint32_t white = SDL_MapRGB(mapSurface->format, 255, 255, 255);
        SDL_Point worldCenter = {(int)currentPlayer->position.x, (int)currentPlayer->position.z};
        SDL_Point mapCenter = {mapRect.w / 2, mapRect.h / 2};
        for (const auto& entity : world.children)
        {
            auto* entity3D = (AEntity3D*)entity.get();
            SDL_Point entityPos = {(int)entity3D->position.x, (int)entity3D->position.z}; // Has to account for angle later
            SDL_Point mapPos = {mapCenter.x + (int)((float)(entityPos.x - worldCenter.x) * mapScale),
                                mapCenter.y + (int)((float)(worldCenter.y - entityPos.y) * mapScale)};
            mapPos = {std::clamp(mapPos.x, 0, mapRect.w), std::clamp(mapPos.y, 0, mapRect.h)};
            pixels[mapRect.w * mapPos.y + mapPos.x] = white;
        }
    }
    SDL_UnlockSurface(mapSurface);

    SDL_Texture* mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_UpdateTexture(mapTexture, &mapRect, mapSurface->pixels, mapSurface->pitch);
    SDL_Point screenCenter = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_Rect dstRect = {screenCenter.x - mapRect.w / 2, screenCenter.y - mapRect.h / 2, mapRect.w, mapRect.h};
    SDL_RenderCopy(renderer, mapTexture, &mapRect, &dstRect);

    SDL_FreeSurface(mapSurface);
    SDL_DestroyTexture(mapTexture);
}
