#pragma once

#include "engine/game_object/Entity3D.h"

class ACharacter : public Entity3D
{
public:
    // Collider collider
    ACharacter(glm::vec3 position, float rotationY, int hp)
        : Entity3D(position, rotationY), hp(hp) {}
protected:
    int hp;
};