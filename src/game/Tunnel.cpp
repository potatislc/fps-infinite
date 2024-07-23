#include <cmath>
#include "Tunnel.h"
#include "Game.h"
#include "engine/Application.h"
#include "engine/ResourceLoader.h"

TunnelLayer::TunnelLayer(Material::Type materialType_, int amountVal)
{
    materialType = materialType_;
    amount = amountVal;
    hp = (float)std::abs(amount) * materials[materialType].hardness;
}

void Tunnel::start()
{
    materialAtlas = ResourceLoader::loadTexture(TEXTURES_PATH"/materials.png");

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

TunnelLayer Tunnel::nextLayer()
{
    TunnelLayer prevTopLayer = layers[floorLayerIndex];
    printf("Dug layer type: %d\n", prevTopLayer.materialType);

    // Shift layers
    if (!layers.empty()) layers.erase(layers.begin() + floorLayerIndex);
    layers.emplace_back(Material::T_STONE, 1);

    return prevTopLayer;
}

void Tunnel::draw(SDL_Renderer* renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 100, 100, 0, 255);
    for (std::size_t i = 0; i < layers.size(); i++)
    {
        SDL_Rect src = { layers[i].materialType * Game::tileSize, 0, Game::tileSize, Game::tileSize };
        SDL_Rect dest = { Application::renderer.viewport.w / 2 - Game::tileHalfSize, (int)i * Game::tileSize, Game::tileSize, Game::tileSize };
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(Application::renderer.sdlRenderer, materialAtlas, &src, &dest, 0.0, &origin, SDL_FLIP_NONE);
    }
}