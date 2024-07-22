#pragma once
#include <array>

#define MATERIALS \
    MATERIAL(T_AIR, C_GAS, 0.0f, 0.0f) \
    MATERIAL(T_DIRT, C_SOLID, 1.0f, 0.1f) \
    MATERIAL(T_STONE, C_SOLID, 3.0f, 0.5f) \
    MATERIAL(T_IRON, C_SOLID, 5.0f, 2.0f) \
    MATERIAL(T_COPPER, C_SOLID, 4.0f, 1.5f) \
    MATERIAL(T_GOLD, C_SOLID, 3.0f, 10.0f) \
    MATERIAL(T_DIAMOND, C_SOLID, 10.0f, 50.0f)

class Material
{
public:
    enum Category
    {
        C_GAS,
        C_LIQUID,
        C_SOLID,
        C_INSTANT_DEATH
    };

    enum Type
    {
#define MATERIAL(type, category, hardness, price) type,
        MATERIALS
#undef MATERIAL
        T_LENGTH
    };

    const Category category;
    const float hardness;
    float price;
};

extern const Material materials[Material::T_LENGTH];