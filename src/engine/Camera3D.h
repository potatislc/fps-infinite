#pragma once

#include "glm/vec3.hpp"
#include "engine/game_object/EntityScene.h"
#include "engine/game_object/AEntity3D.h"

class Camera3D
{
public:
    float fov;
    float halfFov;
    Camera3D(float fov);
    void drawFov(SDL_Renderer* renderer) const;
    void drawFloor(glm::vec3 position, float rotationY);
    // void drawScene(EntityScene<AEntity3D> scene, glm::vec3 position, float rotationY);
};