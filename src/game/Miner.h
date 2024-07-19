#pragma once

#include <cstdio>
#include <array>
#include "Tunnel.h"
#include "../engine/IGameObject.h"

class Miner : IGameObject
{
    void mine(Tunnel tunnel);
public:
    std::size_t depth = 0;
    std::array<std::size_t, MT_LENGTH> oresMined{};
    void start() override;
    void update() override;
    void draw() override;
};
