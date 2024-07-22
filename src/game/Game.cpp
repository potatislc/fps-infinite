#include <SDL.h>
#include "Game.h"
#include "engine/Renderer.h"
#include "engine/Window.h"
#include "engine/Application.h"

uint16_t Game::tilesW = ceil(Application::renderer.viewport.w / tileSize);
uint16_t Game::tilesH = ceil(Application::renderer.viewport.h / tileSize);

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
    for (int x = 0; x < tilesW; x++)
    {
        uint16_t posX = x * tileSize + tileHalfSize;
        SDL_RenderDrawLine(renderTarget, posX, 0, posX, Application::renderer.viewport.w);
    }

    for (int y = 0; y < tilesH; y++)
    {
        uint16_t posY = y * tileSize;
        SDL_RenderDrawLine(renderTarget, 0, posY, Application::renderer.viewport.h, posY);
    }
}

void Game::draw()
{
    SDL_Renderer* renderTarget = Application::renderer.sdlRenderer;

    clearBackground(renderTarget);
    tunnel.draw(renderTarget);
    miner.draw(renderTarget);

    drawDebugGrid(renderTarget);
}
