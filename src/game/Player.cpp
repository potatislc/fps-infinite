#include <iostream>
#include "Player.h"
#include "engine/InputMap.h"
#include "engine/App.h"
#include "Game.h"

void Player::start()
{

}

void Player::update()
{
    const float lookDir = (float)(InputMap::isBoundKeyDown("LookRight") - InputMap::isBoundKeyDown("LookLeft"));
    rotationY += lookDir * Game::settings.mouseSens * App::deltaTime;
    glm::vec2 moveDir = {InputMap::isBoundKeyDown("Right") - InputMap::isBoundKeyDown("Left"),
                         InputMap::isBoundKeyDown("Down") - InputMap::isBoundKeyDown("Up")};
    moveVelocity = glm::clamp(
            moveVelocity + moveDir * accel * App::deltaTime,
            glm::vec2(-1, -1),
            glm::vec2(1, 1));

    if (moveDir.x == 0)
    {
        if (std::abs(moveVelocity.x) <= accel * App::deltaTime) moveVelocity.x = 0;
        moveVelocity.x -= (float)Utils::sgn(moveVelocity.x) * accel * App::deltaTime;
    }

    if (moveDir.y == 0)
    {
        if (std::abs(moveVelocity.y) <= accel * App::deltaTime) moveVelocity.y = 0;
        moveVelocity.y -= (float)Utils::sgn(moveVelocity.y) * accel * App::deltaTime;
    }

    glm::vec2 rotatedMoveVel = Utils::vec2Rotated(moveVelocity, rotationY);
    position += (glm::vec3){rotatedMoveVel.x, 0, rotatedMoveVel.y} * speed * App::deltaTime;
}

void Player::draw(SDL_Renderer *renderer)
{
    // Debug line
    SDL_Point screenCenter = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
                       screenCenter.x,
                       screenCenter.y,
                       screenCenter.x + (int)(moveVelocity.x * 16),
                       screenCenter.y + (int)(moveVelocity.y * 16));
}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}