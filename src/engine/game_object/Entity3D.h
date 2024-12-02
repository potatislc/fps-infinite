#pragma once

#include "AEntity.h"
#include "glm/vec3.hpp"

class Entity3D : public AEntity
{
public:
    float rotationY;
    glm::vec3 position;

    Entity3D(glm::vec3 position, float rotationY)
        : position(position), rotationY(rotationY) {};
    virtual ~Entity3D() = default;
    virtual void start() override {};
    virtual void update() override {};
    virtual void draw(SDL_Renderer* renderer) override {};
    virtual void draw3D(SDL_Renderer* renderer) {};
};