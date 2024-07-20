#pragma once

#include <cstdio>
#include <array>
#include "Tunnel.h"
#include "engine/IGameObject.h"

class Miner : IGameObject
{
    Tunnel* tunnel;

    void mine();
public:
    std::size_t depth = 0;
    std::array<std::size_t, MT_LENGTH> oresMined{};
    Miner(Tunnel* tunnel_);
    void start() override;
    void update() override;
    void draw() override;
};
