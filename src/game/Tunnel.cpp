#include <cstdlib>
#include "Tunnel.h"
#include "Game.h"
#include "engine/Application.h"
#include "engine/ResourceLoader.h"
#include "engine/utils/Utils.h"

Tunnel::Layer::Layer(Material::Type materialType, int amountVal) : materialType(materialType)
{
    amount = amountVal;
    hp = (float)std::abs(amount) * materials[materialType].hardness;
}

void Tunnel::start()
{
    materialAtlas.set(ResourceLoader::loadTexture(TEXTURES_PATH"/materials.png"));

    // All layers before starting layer should be air
    for (uint8_t i = 0; i < floorLayerIndex; i++)
    {
        layers.emplace_back(Material::T_AIR, 1);
    }

    // All layers afterward are dirt for now
    for (uint8_t i = floorLayerIndex; i < activeLayersCount; i++)
    {
        layers.emplace_back(Material::T_DIRT, 1);
    }
}

void Tunnel::update()
{

}

Tunnel::Layer Tunnel::nextLayer()
{
    Layer prevTopLayer = layers[floorLayerIndex];
    printf("Dug layer type: %d\n", prevTopLayer.materialType);

    // Shift layers
    if (!layers.empty()) layers.erase(layers.begin() + floorLayerIndex);
    auto nextMaterialType = (Material::Type)(rand() % Material::T_LENGTH);
    Material nextMaterial = materials[nextMaterialType];
    uint8_t nextVeinLength = Utils::uRandRange(nextMaterial.veinLength.min, nextMaterial.veinLength.max);
    for (uint8_t i = 0; i < nextVeinLength; i++)
    {
        layers.emplace_back(nextMaterialType, 1);
    }

    return prevTopLayer;
}

void Tunnel::drawCenterColumn(SDL_Renderer *renderTarget, uint8_t depth)
{
    for (uint8_t i = 0; i <= depth; i++)
    {
        SDL_Rect src = { layers[i].materialType * Game::tileSize, 0, Game::tileSize, Game::tileSize };
        SDL_Rect dest = { Application::renderer.viewport.w / 2 - Game::tileHalfSize, (int)i * Game::tileSize, Game::tileSize, Game::tileSize };
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(Application::renderer.sdlRenderer, materialAtlas.sdlTexture, &src, &dest, 0.0, &origin, SDL_FLIP_NONE);
    }
}

void Tunnel::drawWalls(SDL_Renderer *renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 100, 100, 100, 255);
    SDL_Rect wallLeft = { Application::renderer.viewport.w / 2 - Game::tileHalfSize - Game::tileSize, 0, Game::tileSize, Application::renderer.viewport.h };
    SDL_Rect wallRight = { Application::renderer.viewport.w / 2 - Game::tileHalfSize + Game::tileSize, 0, Game::tileSize, Application::renderer.viewport.h };
    SDL_RenderFillRect(renderTarget, &wallLeft);
    SDL_RenderFillRect(renderTarget, &wallRight);
}

void Tunnel::draw(SDL_Renderer* renderTarget)
{
    drawCenterColumn(renderTarget, 64/*floorLayerIndex*/);
    drawWalls(renderTarget);
}