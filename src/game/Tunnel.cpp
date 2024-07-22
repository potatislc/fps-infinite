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
    for (uint8_t i = 0; i <= startingLayerIndex; i++)
    {
        layers.emplace_back(Material::T_AIR, 1);
    }

    // All layers afterward are dirt for now
    for (uint8_t i = startingLayerIndex+1; i < activeLayersCount; i++)
    {
        layers.emplace_back(Material::T_DIRT, 1);
    }
}

TunnelLayer Tunnel::nextLayer()
{
    TunnelLayer prevTopLayer = layers[startingLayerIndex];

    // Shift layers
    if (!layers.empty()) layers.erase(layers.begin() + startingLayerIndex);
    layers.emplace_back(Material::T_STONE, 1);

    return prevTopLayer;
}

void Tunnel::draw(SDL_Renderer *renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 100, 100, 0, 255);
    for (std::size_t i = 0; i < layers.size(); i++)
    {
        if (layers[i].materialType != Material::T_AIR)
        {
            SDL_Rect tile = { Application::renderer.viewport.w / 2 - Game::tileHalfSize, (int)i * Game::tileSize, Game::tileSize, Game::tileSize };
            SDL_RenderFillRect(renderTarget, &tile);
        }
    }
}
