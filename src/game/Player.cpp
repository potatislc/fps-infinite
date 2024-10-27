#include <cmath>
#include "Player.h"
#include "engine/App.h"
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

    /*
    SDL_Rect dst = {
            (int)App::renderer.viewportCenter.x,
            (int)App::renderer.viewportCenter.y,
            ResourceLoader::loadedTextures.playerMapIcon.getRect()->w,
            ResourceLoader::loadedTextures.playerMapIcon.getRect()->h
    };
    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.playerMapIcon.get(),
            ResourceLoader::loadedTextures.playerMapIcon.getRect(),
            &dst
            );
    */

    SDL_Point center = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int lineEndX = (int)(std::sin(Game::camera3D.halfFov) * (float)center.y);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x - lineEndX, 0);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + lineEndX, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, center.x, center.y);
}

Player::Player(glm::vec3 position, float rotationY, int hp)
    : ACharacter(position, rotationY, hp)
{

}
