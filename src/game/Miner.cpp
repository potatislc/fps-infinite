#include "Miner.h"
#include "engine/Window.h"
#include "game.h"

Miner::Miner(Tunnel* tunnel_)
{
    tunnel = tunnel_;
}

void Miner::mine()
{
    // Mine current layer
    depth++;
    TunnelLayer currentLayer = tunnel->nextLayer();
    oresMined[currentLayer.material->type] += currentLayer.amount;

    // How miner will react to standing on the new top layer
    switch (tunnel->layers[0].material->type)
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

}

void Miner::draw(SDL_Renderer* renderTarget)
{
    // Temporary ---
    SDL_SetRenderDrawColor(renderTarget, 100, 100, 255, 255);
    SDL_Rect fillRect = {Window::width / 2 - Game::tileHalfSize, Window::height / 2, Game::tileSize, Game::tileSize };
    SDL_RenderFillRect(renderTarget, &fillRect);
    // ---
}
