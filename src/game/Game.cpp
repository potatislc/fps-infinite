#include "Game.h"
#include "engine/Renderer.h"

Game::Game()
{

}

void Game::start()
{

}

void Game::update()
{

}

void Game::clearBackground(SDL_Renderer* renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
    SDL_RenderClear(renderTarget);
}

void Game::draw()
{
    SDL_Renderer* renderTarget = currentRenderer;

    clearBackground(renderTarget);
    miner.draw(renderTarget);
}