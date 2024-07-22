#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Material.h"

class TunnelLayer
{
    float hp;

public:
    Material* material;
    int amount{};

    TunnelLayer(Material* materialVal, int amountVal);
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

