#pragma once

#include "glm/glm.hpp"
#include "engine/game_object/EntityScene.h"
#include "engine/game_object/Entity3D.h"

class Camera3D : public Entity3D
{
public:
    float fov;
    float halfFov;
    float fovScale;
    int farPlane;

    Camera3D(glm::vec3 position, float rotationY, float fov, int farPlane);
    void initFloorSurface();
    void drawFovLines(SDL_Renderer* renderer) const;
    void drawTexture(SDL_Renderer* renderer, const glm::vec3& worldPos);
    void drawFloor(SDL_Renderer* renderer, SDL_Texture* floor);
private:
    SDL_Surface* floorSurface;
    SDL_Rect floorRect = {0, 0};
};