#pragma once

#include "AEntity.h"
#include "glm/vec3.hpp"

class AEntity3D : public AEntity
{
public:
    glm::vec3 position;
    float rotationY;

    AEntity3D(glm::vec3 position, float rotationY)
        : position(position), rotationY(rotationY) {};
    virtual ~AEntity3D() = default;
    virtual void start() override = 0;
    virtual void update() override = 0;
    virtual void draw(SDL_Renderer* renderTarget) override = 0;
};