#pragma once

#include <glm/glm.hpp>
#include "engine/utils/Utils.h"
#include "engine/IGameObject.h"

class CollectionParticle : IGameObject
{
    glm::vec2 position;
    const glm::vec2 targetPosition;
    const float blastSpeed = 500.f;
    glm::vec2 blastVelocity = {0, 0};
    const float blastDecel = 500.f;
    const float pullAccel = 500.f;
    glm::vec2 pullVelocity = {0, 0};
    CollectionParticle(glm::vec2 position, glm::vec2 targetPosition) :
        position(position), targetPosition(targetPosition) {};
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};