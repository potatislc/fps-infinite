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

    const glm::vec3 direction = {InputMap::isBoundKeyDown("Right") - InputMap::isBoundKeyDown("Left"),
                                 0.f,
                                 InputMap::isBoundKeyDown("Up") - InputMap::isBoundKeyDown("Down")
                                 };
    position += direction * speed * App::deltaTime;
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
