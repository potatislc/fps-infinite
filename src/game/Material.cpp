#include "Material.h"

Material materials[MT_LENGTH] =
{
#define MATERIAL(type, category, hardness, price) {category, hardness, price},
    MATERIALS
#undef MATERIAL
};