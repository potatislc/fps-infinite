#pragma once

#include "engine/game_object/AEntity3D.h"

class ACharacter : public AEntity3D
{
public:
    // Collider collider
    ACharacter(glm::vec3 position, float rotationY, int hp)
        : AEntity3D(position, rotationY), hp(hp) {}
protected:
    int hp;
};