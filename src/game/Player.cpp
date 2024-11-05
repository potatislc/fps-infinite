#include "Player.h"
#include "engine/InputMap.h"
#include "engine/App.h"

void Player::start()
{

}

void Player::update()
{
    const glm::vec3 direction = {InputMap::isBoundKeyDown("Right") - InputMap::isBoundKeyDown("Left"),
                                 0.f,
                                 InputMap::isBoundKeyDown("Up") - InputMap::isBoundKeyDown("Down")
                                 };
    position += direction * speed * (float)App::deltaTime;
}

void Player::draw(SDL_Renderer *renderer)
{

}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}
