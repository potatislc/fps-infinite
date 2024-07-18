#include <cmath>
#include "tunnel.h"

Material air = {MT_AIR, MC_GAS, 0.0f, 0.0f};
Material dirt = {MT_DIRT, MC_SOLID, 1.0f, 0.1f};

Layer::Layer(Material *materialVal, int amountVal)
{
    material = materialVal;
    amount = amountVal;
    hp = (float)std::abs(amount) * material->hardness;
}

Tunnel::Tunnel()
{
    // All layers before starting layer should be air
    for (int i = 0; i < startingLayerIndex; i++)
    {
        layers.emplace_back(&air, 1);
    }

    // All layers afterward are dirt for now
    for (int i = startingLayerIndex+1; i < visibleLayerCount; i++)
    {
        layers.emplace_back(&dirt, 1);
    }
}

Layer Tunnel::nextLayer()
{
    Layer prevTopLayer = layers[startingLayerIndex];

    // Shift layers
    if (!layers.empty()) layers.erase(layers.begin() + startingLayerIndex);
    layers.emplace_back(&dirt, 1);

    return prevTopLayer;
}