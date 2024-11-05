#pragma once

#include "ACharacter.h"
#include "glm/vec2.hpp"

class Player : public ACharacter
{
public:
    Player(glm::vec3 position, float rotationY, int hp);
    ~Player() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    glm::vec2 velocity = {0, 0};
    const float speed = 60;
};
