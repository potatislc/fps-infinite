#pragma once
#include "Miner.h"
#include "Tunnel.h"
#include "engine/IGameObject.h"

class Game : public IGameObject
{
public:
    Tunnel tunnel;
    Miner miner = { &tunnel };
    Game();
    void start() override;
    void update() override;
    void draw() override;
};
