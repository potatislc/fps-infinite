#include <cstdlib>
#include "Material.h"

const Material materials[Material::T_LENGTH] =
{
#define MATERIAL(type, category, hardness, price, veinLength, appearanceRate) {Material::category, hardness, price, Material::veinLength, Material::appearanceRate},
    MATERIALS
#undef MATERIAL
};
