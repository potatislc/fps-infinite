#pragma once
#include "miner.h"
#include "tunnel.h"

class Game
{
public:
    Miner miner;
    Tunnel tunnel;
    void start();
    void update();
};
