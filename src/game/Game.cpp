#include <iostream>
#include "Game.h"
#include "engine/InputMap.h"
#include "Player.h"
#include "engine/ResourceLoader.h"
#include "engine/App.h"

std::shared_ptr<Player> Game::currentPlayer = std::make_shared<Player>((glm::vec3){0, 0, 0}, 0, 1);
Renderer::ViewPortCamera Game::mapCamera = Renderer::ViewPortCamera((SDL_Rect){0, 0, 427, 240});
Camera3D Game::camera3D = Camera3D((glm::vec3){0, 0, 0}, 0, 90);
Game::Settings Game::settings;

Game::Game()
{
    InputMap::addKeyBinding("Quit", SDLK_ESCAPE);
    InputMap::addKeyBinding("Left", SDLK_a);
    InputMap::addKeyBinding("Right", SDLK_d);
    InputMap::addKeyBinding("Up", SDLK_w);
    InputMap::addKeyBinding("Down", SDLK_s);
    InputMap::addKeyBinding("LookLeft", SDLK_LEFT);
    InputMap::addKeyBinding("LookRight", SDLK_RIGHT);
}

void Game::start()
{
    ResourceLoader::loadedTextures.loadAll();
    mapCamera.setRenderTarget(App::renderer.sdlRenderer);
    world.addChild(currentPlayer);

    // Test entities
    world.addChild(std::make_shared<Entity3D>((glm::vec3){5, 0, 6}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){-4, 0, -12}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){1, 0, 27}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){30, 0, -36}, 0));

    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            world.addChild(std::make_shared<Entity3D>((glm::vec3){i * 8 - 256, 0, j * 8 - 256}, 0));
        }
    }
}

void Game::update()
{
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED) exit(0);

    camera3D.position = currentPlayer->position;
    camera3D.rotationY = currentPlayer->rotationY;
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
    camera3D.drawFovLines(renderer);
    drawEntitiesDepth(renderer);
    drawEntitiesToMap(renderer);
}

void Game::drawEntitiesToMap(SDL_Renderer* renderer)
{
    SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, mapRect.w, mapRect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SDL_LockSurface(mapSurface);
    {
        auto* pixels = (uint32_t*)mapSurface->pixels;
        glm::vec2 worldCenter = {currentPlayer->position.x, currentPlayer->position.z};
        float worldAngle = -currentPlayer->rotationY;
        for (const auto& entity : world.children)
        {
            glm::vec2 relativePos =
                    Utils::vec2Rotated({entity->position.x - worldCenter.x, entity->position.z - worldCenter.y}, -worldAngle);
            SDL_Point mapPos = {mapCenter.x + (int)relativePos.x, mapCenter.y + (int)relativePos.y};
            float mapDistSq = std::pow(mapPos.x - mapCenter.x, 2) + std::pow(mapPos.y - mapCenter.y, 2);

            float distAlpha = mapDistSq / mapRadiusSq;
            if (distAlpha < 1.f)
            {
                pixels[mapRect.w * mapPos.y + mapPos.x] =
                        SDL_MapRGBA(mapSurface->format, 255, 255, 255, (uint8_t)(255 - 255 * distAlpha));
            }
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

void Game::drawEntitiesDepth(SDL_Renderer* renderer)
{
    glm::vec3 cameraPos = camera3D.position;

    std::sort(world.children.begin(), world.children.end(),
              [&cameraPos](const std::shared_ptr<Entity3D>& a, const std::shared_ptr<Entity3D>& b) {
                  float distA = (a->position.x - cameraPos.x) * (a->position.x - cameraPos.x)
                                       + (a->position.z - cameraPos.z) * (a->position.z - cameraPos.z);
                  float distB = (b->position.x - cameraPos.x) * (b->position.x - cameraPos.x)
                                       + (b->position.z - cameraPos.z) * (b->position.z - cameraPos.z);
                  return distA > distB;
              });

    for (const std::shared_ptr<Entity3D>& entity : world.children)
    {
        camera3D.drawTexture(renderer, entity->position);
    }
}
