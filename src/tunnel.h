#pragma once

#include <cstdint>
#include <vector>

enum MaterialType
{
    MT_AIR,
    MT_DIRT,
    MT_STONE,
    MT_IRON,
    MT_COPPER,
    MT_GOLD,
    MT_DIAMOND,
    MT_LENGTH
};

enum MaterialCategory
{
    MC_GAS,
    MC_LIQUID,
    MC_SOLID,
    MC_INSTANT_DEATH
};

class Material
{
public:
    MaterialType type;
    MaterialCategory category;
    const float hardness;
    float price;
};

extern Material air;
extern Material dirt;

class Layer
{
    float hp;

public:
    Material* material;
    int amount{};

    Layer(Material* materialVal, int amountVal);
};


class Tunnel
{
    const uint8_t visibleLayerCount = 10;
    uint8_t startingLayerIndex = visibleLayerCount / 2;
public:
    std::vector<Layer> layers;

    Tunnel();

    Layer nextLayer();
};

