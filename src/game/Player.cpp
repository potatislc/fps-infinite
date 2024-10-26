#include "Player.h"
#include "engine/ResourceLoader.h"

void Player::start() {

}

void Player::update()
{

}

void Player::draw(SDL_Renderer *renderer)
{

}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{
    mapIcon = ResourceLoader::loadedTextures.playerMapIcon.get();
}
