#pragma once

#include "ACharacter.h"
#include "Player.h"
#include "engine/Camera3D.h"
#include "engine/collision/Collider.h"

class Eye : public ACharacter
{
public:
    std::shared_ptr<Player> player;
    const float accel = 10;
    const float maxSpeed = 10;
    const float hoverHeight = 2;
    const float hoverMag = 1;
    static float globalHoverOffset;
    float hoverOffset = 0;
    Collider collider = Collider(this, new ShapeCircle(), new Collider::SolidCollision2D(), &position);

    Eye(glm::vec3 position, float rotationY, int hp, std::shared_ptr<Player>& player);
    ~Eye() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
};
