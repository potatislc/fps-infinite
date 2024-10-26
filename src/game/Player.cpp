#include "Player.h"
#include "engine/ResourceLoader.h"
#include "Game.h"

void Player::start()
{

}

void Player::update()
{

}

void Player::draw(SDL_Renderer *renderer)
{
    /*
    Game::mapCamera.drawTexture(
            ResourceLoader::loadedTextures.playerMapIcon.get(),
            ResourceLoader::loadedTextures.playerMapIcon.getRect(),
            ResourceLoader::loadedTextures.playerMapIcon.getRect()
            );
    */

    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.playerMapIcon.get(),
            ResourceLoader::loadedTextures.playerMapIcon.getRect(),
            ResourceLoader::loadedTextures.playerMapIcon.getRect()
            );

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}
