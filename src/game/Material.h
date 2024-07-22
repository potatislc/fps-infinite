#pragma once
#include <array>

enum MaterialCategory
{
    MC_GAS,
    MC_LIQUID,
    MC_SOLID,
    MC_INSTANT_DEATH
};

#define MATERIALS \
    MATERIAL(MT_AIR, MC_GAS, 0.0f, 0.0f) \
    MATERIAL(MT_DIRT, MC_SOLID, 1.0f, 0.1f) \
    MATERIAL(MT_STONE, MC_SOLID, 3.0f, 0.5f) \
    MATERIAL(MT_IRON, MC_SOLID, 5.0f, 2.0f) \
    MATERIAL(MT_COPPER, MC_SOLID, 4.0f, 1.5f) \
    MATERIAL(MT_GOLD, MC_SOLID, 3.0f, 10.0f) \
    MATERIAL(MT_DIAMOND, MC_SOLID, 10.0f, 50.0f)

enum MaterialType
{
#define MATERIAL(type, category, hardness, price) type,
    MATERIALS
#undef MATERIAL
    MT_LENGTH
};

class Material
{
public:
    MaterialCategory category;
    const float hardness;
    float price;
};

extern Material materials[MT_LENGTH];