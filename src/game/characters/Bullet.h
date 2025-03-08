#pragma once

#include "glm/vec3.hpp"
#include "engine/game_object/Entity3D.h"

class Bullet : public Entity3D
{
public:
    Bullet(glm::vec3 position, float rotationZ, glm::vec3 direction);
    void update() override;

private:
    float speed = 60;
    glm::vec3 velocity;
};
