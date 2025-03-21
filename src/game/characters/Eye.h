#pragma once

#include "ACharacter.h"
#include "Player.h"
#include "engine/Camera3D.h"
#include "engine/Id.h"

class Eye : public ACharacter
{
public:
    std::shared_ptr<Player> player;
    const float accel = 16;
    const float maxSpeed = 16;
    const float hoverHeight = 2;
    const float hoverMag = 1;
    static float globalHoverOffset;
    float hoverOffset = 0;
    id_t colliderId = 0;

    Eye(glm::vec3 position, float rotationY, int hp, std::shared_ptr<Player>& player);
    ~Eye() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
};
