#include <iostream>
#include "Player.h"
#include "engine/InputMap.h"
#include "engine/App.h"
#include "game/Game.h"

void Player::start()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
}

void Player::update()
{
    // const float lookDir = (float)(InputMap::isBoundKeyDown("LookRight") - InputMap::isBoundKeyDown("LookLeft"));
    rotationZ += InputMap::mouseMotion.x * Game::settings.mouseSens;
    rotationZ = Utils::fmod(rotationZ, (float)M_PI * 2.f);
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

    glm::vec2 rotatedMoveVel = Utils::vec2Rotate(moveVelocity, rotationZ);
    velocity = (glm::vec3){rotatedMoveVel.x, rotatedMoveVel.y, 0};
    position += velocity * speed * App::deltaTime;

    if (InputMap::isBoundKeyDown("FlyUp")) position.z += 10 * App::deltaTime;
    if (InputMap::isBoundKeyDown("FlyDown")) position.z -= 10 * App::deltaTime;

    if (glm::length(moveVelocity) > 0 || headBobPhase > 0)
    {
        headBobPhase += headBobSpeed * App::deltaTime;
        if (headBobPhase >= M_PI * 2) headBobPhase = 0;
    }

    headBob = -glm::sin(headBobPhase) * (glm::length(moveVelocity * ((glm::length(moveVelocity) > 0) ? glm::normalize(moveVelocity) : glm::vec2(1, 1)))) * headBobMag;

    Game::camera3D.position = position + glm::vec3{
        0,
        0,
        eyeHeight + headBob};
    Game::camera3D.rotationZ = rotationZ + (float)(M_PI / 2);
}

void Player::draw(SDL_Renderer *renderer)
{
    // Debug line
    /*SDL_Point screenCenter = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
                       screenCenter.x,
                       screenCenter.y,
                       screenCenter.x + (int)(moveVelocity.x * 16),
                       screenCenter.y + (int)(moveVelocity.y * 16));*/
}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}
