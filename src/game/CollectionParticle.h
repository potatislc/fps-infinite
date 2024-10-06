#pragma once

#include <glm/glm.hpp>
#include "engine/utils/Utils.h"
#include "engine/IGameObject.h"
#include "engine/GameScene.h"

class CollectionParticle : ASceneObject
{
    glm::vec2 position;
    const glm::vec2 targetPosition;
    const float blastSpeed = 800.f;
    glm::vec2 blastVelocity = {0, 0};
    const float blastDecel = 3000.f;
    const float pullSpeed = 1000.f;
    glm::vec2 pullVelocity = {0, 0};
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

public:
    CollectionParticle(glm::vec2 position, glm::vec2 targetPosition) :
        position(position), targetPosition(targetPosition) {}
};