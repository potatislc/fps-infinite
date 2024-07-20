#include "Miner.h"

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

void Miner::draw()
{

}
