#pragma once

#include "glm/glm.hpp"
#include "engine/game_object/EntityScene.h"
#include "engine/game_object/Entity3D.h"
#include "UniqueTexture.h"

class Camera3D : public Entity3D
{
public:
    float fov;
    float halfFov;
    float fovScale;
    int farPlane;

    Camera3D(glm::vec3 position, float rotationY, float fov, int farPlane);
    static void initFloorProjectionSurface(SDL_Surface*& surface, int w, int h);
    void drawFovLines(SDL_Renderer* renderer) const;
    void drawTexture3D(SDL_Renderer* renderer, UniqueTexture& uniqueTexture, const glm::vec3& targetPoint,
                       float targetRotZ, SDL_Rect& viewport);
    void drawFloor(SDL_Renderer* renderer, SDL_Surface* floorSurface, UniqueTexture& floorTexture);
};