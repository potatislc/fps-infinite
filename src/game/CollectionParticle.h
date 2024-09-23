#pragma once

#include "engine/utils/Utils.h"
#include "engine/IGameObject.h"

class CollectionParticle : IGameObject
{
    Utils::Vector2 position;
    const Utils::Vector2 targetPosition;
    const float blastSpeed = 500.f;
    Utils::Vector2 blastVelocity = {0, 0};
    const float blastDecel = 500.f;
    const float pullAccel = 500.f;
    Utils::Vector2 pullVelocity = {0, 0};
    CollectionParticle(Utils::Vector2 position, Utils::Vector2 targetPosition) :
        position(position), targetPosition(targetPosition) {};
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};