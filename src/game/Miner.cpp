#include "Miner.h"
#include "game.h"
#include "engine/Application.h"
#include "engine/InputMap.h"
#include "engine/ResourceLoader.h"

Miner::Miner(Tunnel* tunnel) : tunnel(tunnel) { }

void Miner::mine()
{
    // Mine current layer
    depth++;
    Tunnel::Layer currentLayer = tunnel->nextLayer();
    materialsMined[currentLayer.materialType] += currentLayer.amount;

    // How miner will react to standing on the new top layer
    switch (tunnel->layers[0].materialType)
    {
        default:
            // Default is an ore you can stand on and mine regularly
            break;
    }

    mined.send(depth);
}

void Miner::start()
{
    mockupLook.set(ResourceLoader::loadTexture(TEXTURES_PATH"miner/mockup.png"));
}

void Miner::update()
{
    if (InputMap::getBoundKeyInput("Dig") == InputMap::S_PRESSED || InputMap::getBoundMouseInput("Dig") == InputMap::S_PRESSED)
    {
        mine();
    }
}

void Miner::draw(SDL_Renderer* renderTarget)
{
    SDL_SetRenderDrawColor(renderTarget, 100, 100, 255, 255);
    SDL_Rect fillRect = {Application::renderer.viewport.w / 2 - Game::tileHalfSize, Application::renderer.viewport.h / 2, Game::tileSize, Game::tileSize };
    // SDL_RenderFillRect(renderTarget, &fillRect);
    SDL_Rect source = {0, 0, mockupLook.getSize().x, mockupLook.getSize().y};
    SDL_Rect dest = {Application::renderer.viewport.w / 2 - Game::tileHalfSize, Application::renderer.viewport.h / 2 - Game::tileSize, 31, Game::tileSize * 2};
    SDL_RenderCopy(renderTarget, mockupLook.get(), &source, &dest);
}
