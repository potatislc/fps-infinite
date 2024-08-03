#pragma once
#include <array>
#include <cstdint>

#define MATERIALS \
    MATERIAL(T_AIR, C_GAS, 0.f, 0.f, VeinLength(2, 16), AppearanceRate(.1f, 0.01f)) \
    MATERIAL(T_DIRT, C_SOLID, 1.f, .1f, VeinLength(1, 8), AppearanceRate(3.f, -.01f)) \
    MATERIAL(T_STONE, C_SOLID, 3.f, .5f, VeinLength(1, 4), AppearanceRate(5.f, .005f)) \
    MATERIAL(T_IRON, C_SOLID, 5.f, 2.f, VeinLength(1, 5), AppearanceRate(.4f, .0f)) \
    MATERIAL(T_COPPER, C_SOLID, 4.f, 1.5f, VeinLength(2, 12), AppearanceRate(.2f, .01f)) \
    MATERIAL(T_GOLD, C_SOLID, 3.f, 10.f, VeinLength(3, 6), AppearanceRate(.2f, .01f)) \
    MATERIAL(T_DIAMOND, C_SOLID, 10.f, 50.f, VeinLength(1, 9), AppearanceRate(.1f, .01f)) \
    MATERIAL(T_LAVA, C_LIQUID, 0.f, 0.f, VeinLength(1, 1), AppearanceRate(.1f, .01f))

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
#define MATERIAL(type, category, hardness, price, veinLength, appearanceRate) type,
        MATERIALS
#undef MATERIAL
        T_LENGTH
    };

    struct VeinLength
    {
        uint8_t min;
        uint8_t max;

        VeinLength(uint8_t min, uint8_t max) : min(min), max(max) {}
    };

    struct AppearanceRate
    {
        const float initial;
        float current {};
        float delta {};

        AppearanceRate(float initial, float delta) : initial(initial), current(initial), delta(delta) {}
    };

    const Category category;
    const float hardness;
    float price;
    VeinLength veinLength;
    AppearanceRate appearanceRate;
};

extern const Material materials[Material::T_LENGTH];