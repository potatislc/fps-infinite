#include <iostream>
#include <thread>
#include "Game.h"
#include "engine/InputMap.h"
#include "Player.h"
#include "engine/ResourceLoader.h"
#include "engine/App.h"

std::shared_ptr<Player> Game::currentPlayer = std::make_shared<Player>((glm::vec3){0, 0, 0}, 0, 1);
Renderer::ViewPortCamera Game::mapCamera = Renderer::ViewPortCamera((SDL_Rect){0, 0, 426, 240});
Camera3D Game::camera3D = Camera3D((glm::vec3){0, 0, 0}, 0, 90, 180);
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
    camera3D.initFloorSurface();
    mapCamera.setRenderTarget(App::renderer.sdlRenderer);
    world.addChild(currentPlayer);

    // Test entities
    world.addChild(std::make_shared<Entity3D>((glm::vec3){5, 6, 1}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){-4, -12, 2}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){1, 27, 10}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){30, -36, 6}, 0));

    /*for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            world.addChild(std::make_shared<Entity3D>((glm::vec3){i * 4 - 1 * 64, j * 4 - 1 * 64, glm::sin(j) + 1}, 0));
        }
    }*/
}

void Game::update()
{
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED) exit(0);

    camera3D.position = currentPlayer->position;
    camera3D.rotationY = currentPlayer->rotationY + (float)(M_PI / 2);
    world.update();
}

void Game::draw(SDL_Renderer *renderer)
{
    SDL_Rect rect = {0, 0, App::renderer.viewport.w, App::renderer.viewport.h};
    SDL_Texture *renderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    SDL_SetRenderTarget(renderer, renderTarget);
        camera3D.drawFloor(renderer, ResourceLoader::loadedTextures.testFloor);
        drawBackground(renderer);
        drawEntitiesDepth(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, renderTarget, nullptr, nullptr);
    SDL_DestroyTexture(renderTarget);

    drawEntitiesToMap(renderer);
    drawMap(renderer);
    // camera3D.drawFovLines(renderer);
}

void Game::drawEntitiesToMap(SDL_Renderer* renderer)
{
    SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, mapRect.w, mapRect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SDL_LockSurface(mapSurface);
    {
        auto* pixels = (uint32_t*)mapSurface->pixels;
        glm::vec3 worldCenter = currentPlayer->position;
        float worldRotationY = -currentPlayer->rotationY;
        for (const auto& entity : world.children)
        {
            glm::vec2 relativePos =
                    Utils::vec2Rotated(entity->position - worldCenter, worldRotationY);
            SDL_Point mapPos = {mapCenter.x + (int)relativePos.x, mapCenter.y + (int)relativePos.y};
            auto dx = static_cast<float>(mapPos.x - mapCenter.x);
            auto dy = static_cast<float>(mapPos.y - mapCenter.y);
            float mapDistSq = dx * dx + dy * dy;

            float distAlpha = mapDistSq / mapRadiusSq;
            if (distAlpha < 1.f)
            {
                pixels[mapRect.w * mapPos.y + mapPos.x] =
                        SDL_MapRGBA(mapSurface->format, 255, 255, 255, (uint8_t)(255 - 255 * distAlpha));
            }
        }
    }
    SDL_UnlockSurface(mapSurface);

    mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_UpdateTexture(mapTexture, &mapRect, mapSurface->pixels, mapSurface->pitch);
    SDL_FreeSurface(mapSurface);
}

void Game::drawEntitiesDepth(SDL_Renderer* renderer)
{
    glm::vec3 cameraPos = camera3D.position;
    float cameraAngle = camera3D.rotationY;
    float halfFov = camera3D.halfFov;
    auto farPlaneSquared = static_cast<float>(camera3D.farPlane * camera3D.farPlane);
    std::vector<std::pair<float, Entity3D*>> entityDistances;

    for (const auto& entity : world.children)
    {
        if (entity.get() != currentPlayer.get())
        {
            glm::vec2 pointDir2D = {camera3D.position.x - entity->position.x, cameraPos.y - entity->position.y};
            float pointAngle = std::atan2(pointDir2D.y, pointDir2D.x);
            float angleBetween = std::atan2(std::sin(pointAngle - cameraAngle), std::cos(pointAngle - cameraAngle));
            float distSquared = (entity->position.x - cameraPos.x) * (entity->position.x - cameraPos.x) +
                                (entity->position.y - cameraPos.y) * (entity->position.y - cameraPos.y);
            if (angleBetween < halfFov && angleBetween > -halfFov && distSquared < farPlaneSquared)
            {
                entityDistances.emplace_back(distSquared, entity.get());
            }
        }
    }

    std::sort(entityDistances.begin(), entityDistances.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    UniqueTexture& testTex = ResourceLoader::loadedTextures.swarm;
    SDL_Rect& viewport = App::renderer.viewport;
    for (const auto& [_, entity] : entityDistances)
    {
        camera3D.drawTexture3D(renderer, testTex, entity->position, viewport);
    }
}

void Game::drawBackground(SDL_Renderer* renderer)
{
    SDL_Rect dst = *ResourceLoader::loadedTextures.testBg.getRect();
    dst.x = (int)((dst.w / M_PI_2) * -camera3D.rotationY * .25f) % dst.w;
    dst.h++;

    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.testBg.get(),
            ResourceLoader::loadedTextures.testBg.getRect(),
            &dst);

    dst.x -= dst.w * Utils::sgn(dst.x);

    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.testBg.get(),
            ResourceLoader::loadedTextures.testBg.getRect(),
            &dst);
}

void Game::drawMap(SDL_Renderer* renderer)
{
    SDL_Point screenCenter = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_Rect dstRect = {screenCenter.x - mapRect.w / 2, screenCenter.y - mapRect.h / 2, mapRect.w, mapRect.h};
    SDL_RenderCopy(renderer, mapTexture, &mapRect, &dstRect);

    SDL_DestroyTexture(mapTexture);
}
