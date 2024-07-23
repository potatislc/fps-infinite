#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Material.h"

class TunnelLayer
{
    float hp;

public:
    Material::Type materialType;
    int amount{};

    TunnelLayer(Material::Type materialType_, int amountVal);
};

class Tunnel
{
    const uint8_t activeLayersCount = 16;
    uint8_t floorLayerIndex = (activeLayersCount / 2) + 1;
    SDL_Texture* materialAtlas = nullptr;
public:
    std::vector<TunnelLayer> layers;

    Tunnel();
    TunnelLayer nextLayer();
    void draw(SDL_Renderer* renderTarget);
};

