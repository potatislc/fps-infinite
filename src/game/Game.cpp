#include <SDL.h>
#include "Game.h"
#include "engine/Renderer.h"

Game::Game() = default;

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

void Game::drawDebugGrid(SDL_Renderer *renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);

}

void Game::draw()
{
    SDL_Renderer* renderTarget = Renderer::sdlRenderer;

    clearBackground(renderTarget);
    drawDebugGrid(renderTarget);
    tunnel.draw(renderTarget);
    miner.draw(renderTarget);
}
