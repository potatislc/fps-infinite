#include <SDL.h>
#include <ctime>
#include "Game.h"
#include "engine/Application.h"

uint8_t Game::tileCountX;
uint8_t Game::tileCountY;

void Game::start()
{
    std::srand(std::time(nullptr));

    tileCountX = ceil(Application::renderer.viewport.w / tileSize);
    tileCountY = ceil(Application::renderer.viewport.h / tileSize);

    tunnel.start();
    miner.start();
}

void Game::update()
{
    miner.update();
}

void Game::clearBackground(SDL_Renderer* renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
    SDL_RenderClear(renderTarget);
}

void Game::drawDebugGrid(SDL_Renderer *renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 50, 50, 50, 255);
    for (uint8_t x = 0; x < tileCountX; x++)
    {
        uint16_t posX = x * tileSize + tileHalfSize;
        SDL_RenderDrawLine(renderTarget, posX, 0, posX, Application::renderer.viewport.w);
    }

    for (uint8_t y = 0; y < tileCountY; y++)
    {
        uint16_t posY = y * tileSize;
        SDL_RenderDrawLine(renderTarget, 0, posY, Application::renderer.viewport.h, posY);
    }
}

void Game::draw(SDL_Renderer* renderTarget)
{
    clearBackground(renderTarget);
    miner.draw(renderTarget);
    tunnel.draw(renderTarget);

    drawDebugGrid(renderTarget);
}
