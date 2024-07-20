#include "Miner.h"
#include "engine/Window.h"

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

void Miner::draw(SDL_Renderer* sdlRenderer)
{
    // Temporary ---
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 255);
    SDL_Rect fillRect = { Window::screenWidth / 4, Window::screenHeight / 4, Window::screenWidth / 2, Window::screenHeight / 2 };
    SDL_RenderFillRect(sdlRenderer, &fillRect);
    // ---
}
