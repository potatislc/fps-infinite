#include <iostream>
#include "Player.h"
#include "engine/InputMap.h"
#include "engine/App.h"
#include "game/Game.h"
#include "Bullet.h"

void Player::start()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
}

void Player::update()
{
    // const float lookDir = (float)(InputMap::isBoundKeyDown("LookRight") - InputMap::isBoundKeyDown("LookLeft"));
    rotationZ += InputMap::mouseMotion.x * Game::settings.mouseSens.x;
    rotationZ = Utils::fmod(rotationZ, (float)M_PI * 2.f);
    glm::vec2 moveDir = {InputMap::isBoundKeyDown("Right") - InputMap::isBoundKeyDown("Left"),
                         InputMap::isBoundKeyDown("Down") - InputMap::isBoundKeyDown("Up")};
    moveVel = glm::clamp(
            moveVel + moveDir * accelSpeed * App::deltaTime,
            glm::vec2(-1, -1),
            glm::vec2(1, 1));

    aimY = std::clamp(aimY + InputMap::mouseMotion.y * Game::settings.mouseSens.y, -64.f, 64.f);

    if (moveDir.x == 0)
    {
        if (std::abs(moveVel.x) <= accelSpeed * App::deltaTime) moveVel.x = 0;
        moveVel.x -= (float)Utils::sgn(moveVel.x) * accelSpeed * App::deltaTime;
    }

    if (moveDir.y == 0)
    {
        if (std::abs(moveVel.y) <= accelSpeed * App::deltaTime) moveVel.y = 0;
        moveVel.y -= (float)Utils::sgn(moveVel.y) * accelSpeed * App::deltaTime;
    }

    /*if (InputMap::isBoundKeyPressed("Jump") && grounded)
    {
        velocity.z = jumpForce;
        grounded = false;
    }*/

    glm::vec2 rotatedMoveVelocity = Utils::vec2Rotate(moveVel, rotationZ);
    velocity = glm::vec3{rotatedMoveVelocity * moveSpeed, velocity.z - gravity * App::deltaTime};

    position += velocity * App::deltaTime;

    if (position.z < 0)
    {
        grounded = true;
        position.z = 0;
        velocity.z = 0;
    }

    /*if (InputMap::isBoundKeyDown("FlyUp")) position.z += 10 * App::deltaTime;
    if (InputMap::isBoundKeyDown("FlyDown")) position.z -= 10 * App::deltaTime;*/

    if (glm::length(moveVel) > 0 || headBobPhase > 0)
    {
        headBobPhase += headBobSpeed * App::deltaTime;
        if (headBobPhase >= M_PI * 2) headBobPhase = 0;
    }

    headBob = -glm::sin(headBobPhase) * (glm::length(moveVel * ((glm::length(moveVel) > 0) ? glm::normalize(moveVel) : glm::vec2(1, 1)))) * headBobMag;

    Game::camera3D.position = position + glm::vec3{
        0,
        0,
        eyeHeight + headBob};
    Game::camera3D.rotationZ = rotationZ + (float)(M_PI / 2);

    if (InputMap::isBoundMouseButtonDown("Shoot"))
    {
        float ndcY = 1.0f - (2.0f * (App::renderer.viewportCenter.y + aimY)) / App::renderer.viewport.h;

        float fovTan = glm::tan(Game::camera3D.fov / 2.0f);
        forward = glm::vec3{glm::cos(rotationZ - M_PI_2), glm::sin(rotationZ - M_PI_2), ndcY * fovTan};
        auto bulletInstance = std::make_shared<Bullet>(Bullet(position + glm::vec3(0, 0, 1.2f), rotationZ, forward));
        Game::world.queueAddChild(bulletInstance);
    }
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
