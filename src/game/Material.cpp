#include "Material.h"

Material materials[Material::T_LENGTH] =
{
#define MATERIAL(type, category, hardness, price) {Material::category, hardness, price},
    MATERIALS
#undef MATERIAL
};