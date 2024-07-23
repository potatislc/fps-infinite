#include <cmath>
#include "Tunnel.h"
#include "Game.h"
#include "engine/Application.h"

TunnelLayer::TunnelLayer(Material::Type materialType_, int amountVal)
{
    materialType = materialType_;
    amount = amountVal;
    hp = (float)std::abs(amount) * materials[materialType].hardness;
}

Tunnel::Tunnel()
{
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
        if (layers[i].materialType != Material::T_AIR)
        {
            SDL_Rect tile = { Application::renderer.viewport.w / 2 - Game::tileHalfSize, (int)i * Game::tileSize, Game::tileSize, Game::tileSize };
            if (layers[i].materialType == Material::T_STONE) SDL_SetRenderDrawColor(renderTarget, 100, 100, 100, 255);
            SDL_RenderFillRect(renderTarget, &tile);
        }
    }
}
