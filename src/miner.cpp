#include "miner.h"


void Miner::mine(Tunnel tunnel)
{
    // Mine current layer
    depth++;
    Layer currentLayer = tunnel.nextLayer();
    oresMined[currentLayer.material->type] += currentLayer.amount;

    // How miner will react to standing on the new top layer
    switch (tunnel.layers[0].material->type)
    {
        default:
            // Default is an ore you can stand on and mine regularly
            break;
    }
}