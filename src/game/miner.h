#pragma once

#include <cstdio>
#include <array>
#include "tunnel.h"

class Miner
{
public:
    std::size_t depth = 0;
    std::array<std::size_t, MT_LENGTH> oresMined{};
    void mine(Tunnel tunnel);
};
