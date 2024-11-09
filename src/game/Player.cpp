#include "Player.h"
#include "engine/InputMap.h"
#include "engine/App.h"
#include "Game.h"

void Player::start()
{

}

void Player::update()
{
    const float lookDir = (float)(InputMap::isBoundKeyDown("LookLeft") - InputMap::isBoundKeyDown("LookRight"));
    rotationY += lookDir * Game::settings.mouseSens * App::deltaTime;

    const glm::vec2 moveDir = Utils::vec2Rotated(
            {InputMap::isBoundKeyDown("Right") - InputMap::isBoundKeyDown("Left"),
             InputMap::isBoundKeyDown("Down") - InputMap::isBoundKeyDown("Up")
             }, -rotationY);

    position += (glm::vec3){moveDir.x, 0.f, moveDir.y} * speed * App::deltaTime;
}

void Player::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Point pos2D = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_RenderDrawLine(renderer, pos2D.x, pos2D.y, pos2D.x + std::cos(rotationY) * 8, pos2D.y + std::sin(rotationY) * 8);
}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}
