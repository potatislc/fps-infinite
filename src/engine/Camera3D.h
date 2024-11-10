#pragma once

#include "glm/glm.hpp"
#include "engine/game_object/EntityScene.h"
#include "engine/game_object/Entity3D.h"

class Camera3D : public Entity3D
{
public:
    float fov;
    float halfFov;

    Camera3D(glm::vec3 position, float rotationY, float fov);
    void drawFovLines(SDL_Renderer* renderer) const;
    void drawTexture(SDL_Renderer* renderer, glm::vec3 worldPos);
};