#pragma once

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