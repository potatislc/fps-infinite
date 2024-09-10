#include <SDL.h>
#include <ctime>
#include "Game.h"
#include "engine/Application.h"
#include "engine/InputMap.h"

uint8_t Game::tileCountX;
uint8_t Game::tileCountY;

Game::Game()
{
    InputMap::addKeyBinding("Dig", SDLK_SPACE);
    InputMap::addKeyBinding("Quit", SDLK_ESCAPE);
}

void Game::start()
{
    std::srand(std::time(nullptr));

    tileCountX = ceil(Application::renderer.viewport.w / tileSize);
    tileCountY = ceil(Application::renderer.viewport.h / tileSize);

    tunnel.start();
    miner.start();
    uiGameplay.start();
}

void Game::update()
{
    miner.update();
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED) exit(0);
}

void Game::clearBackground(SDL_Renderer* renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
    SDL_RenderClear(renderTarget);
}

void Game::drawDebugGrid(SDL_Renderer *renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 50, 50, 50, 255);
    for (int x = 0; x < tileCountX; x++)
    {
        int posX = x * tileSize + tileHalfSize;
        SDL_RenderDrawLine(renderTarget, posX, 0, posX, Application::renderer.viewport.w);
    }

    for (int y = 0; y < tileCountY; y++)
    {
        int posY = y * tileSize;
        SDL_RenderDrawLine(renderTarget, 0, posY, Application::renderer.viewport.h, posY);
    }
}

void Game::draw(SDL_Renderer* renderTarget)
{
    clearBackground(renderTarget);
    miner.draw(renderTarget);
    tunnel.draw(renderTarget);

    // drawDebugGrid(renderTarget);

    uiGameplay.draw(renderTarget);
}