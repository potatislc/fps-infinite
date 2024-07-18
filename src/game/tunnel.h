#pragma once
#include <cstdint>
#include <vector>
#include "material.h"

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
    const uint8_t visibleLayerCount = 10;
    uint8_t startingLayerIndex = visibleLayerCount / 2;
public:
    std::vector<TunnelLayer> layers;

    Tunnel();

    TunnelLayer nextLayer();
};

