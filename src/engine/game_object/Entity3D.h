#pragma once

#include "AEntity.h"
#include "glm/vec3.hpp"

class Entity3D : public AEntity
{
public:
    float rotationZ;
    glm::vec3 position;
    glm::vec3 forward = glm::vec3(0, 0, 0);
    
    Entity3D(glm::vec3 position, float rotationZ)
        : rotationZ(rotationZ), position(position) {};
    virtual ~Entity3D() = default;
    virtual void start() override {};
    virtual void update() override {};
    void draw(SDL_Renderer* renderer) override {};
    // virtual void draw3D(SDL_Renderer* renderer) {};
};