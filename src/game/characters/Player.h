#pragma once

#include "ACharacter.h"
#include "glm/glm.hpp"

class Player : public ACharacter
{
public:
    float headBob = 0.f;

    Player(glm::vec3 position, float rotationY, int hp);
    ~Player() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    glm::vec2 moveVelocity = {0, 0};
    const float speed = 18;
    const float accel = 4;
    float eyeHeight = 2;
    float totalMoveDist = 0.f;
    float headBobPhase = 0.f;
    const float headBobSpeed = 10;
    const float headBobMag = .25f;
};
