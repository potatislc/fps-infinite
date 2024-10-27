#pragma once

#include "glm/vec3.hpp"
#include "engine/game_object/EntityScene.h"

class Camera3D
{
public:
    float fov;
    float halfFov;
    Camera3D(float fov);
    void drawFloor(glm::vec3 position, float rotationY);
    void drawScene(EntityScene scene, glm::vec3 position, float rotationY);
};