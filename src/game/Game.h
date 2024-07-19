#pragma once
#include "Miner.h"
#include "Tunnel.h"
#include "engine/IGameObject.h"

class Game : public IGameObject
{
public:
    Miner miner;
    Tunnel tunnel;
    void start() override;
    void update() override;
    void draw() override;
};
