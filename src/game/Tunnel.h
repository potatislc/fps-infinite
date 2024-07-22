#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Material.h"

class TunnelLayer
{
    float hp;

public:
    MaterialType materialType;
    int amount{};

    TunnelLayer(MaterialType materialType_, int amountVal);
};


class Tunnel
{
    const uint8_t activeLayersCount = 16;
    uint8_t startingLayerIndex = activeLayersCount / 2;
public:
    std::vector<TunnelLayer> layers;

    Tunnel();
    TunnelLayer nextLayer();
    void draw(SDL_Renderer* renderTarget);
};

