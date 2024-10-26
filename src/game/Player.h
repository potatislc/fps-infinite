#pragma once

#include "ACharacter.h"

class Player : public ACharacter
{
public:
    Player(glm::vec3 position, float rotationY, int hp);
    ~Player() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:
    SDL_Texture* mapIcon = nullptr;
};
