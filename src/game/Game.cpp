#include "Game.h"
#include "engine/InputMap.h"
#include "Player.h"
#include "engine/ResourceLoader.h"

Game::Game()
{
    ResourceLoader::loadedTextures.loadAll();

    InputMap::addKeyBinding("Quit", SDLK_ESCAPE);
    InputMap::addKeyBinding("Left", SDLK_a);
    InputMap::addKeyBinding("Right", SDLK_d);
    InputMap::addKeyBinding("Up", SDLK_w);
    InputMap::addKeyBinding("Down", SDLK_s);

    world.addChild(std::make_unique<Player>((glm::vec3){0, 0, 0}, 0, 1));
}


void Game::start()
{

}

void Game::update()
{
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED) exit(0);
}

void Game::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 50, 0, 175, 255);
    SDL_RenderClear(renderer);
}