#include "Miner.h"
#include "game.h"
#include "engine/Application.h"
#include "engine/InputMap.h"

Miner::Miner(Tunnel* tunnel_)
{
    tunnel = tunnel_;
}

void Miner::mine()
{
    // Mine current layer
    depth++;
    TunnelLayer currentLayer = tunnel->nextLayer();
    materialsMined[currentLayer.materialType] += currentLayer.amount;

    // How miner will react to standing on the new top layer
    switch (tunnel->layers[0].materialType)
    {
        default:
            // Default is an ore you can stand on and mine regularly
            break;
    }
}

void Miner::start()
{

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
    SDL_RenderFillRect(renderTarget, &fillRect);
}
