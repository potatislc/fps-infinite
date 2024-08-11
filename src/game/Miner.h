#pragma once

#include <cstdio>
#include <array>
#include "Tunnel.h"
#include "engine/IGameObject.h"
#include "SDL_render.h"
#include "engine/Event.h"

class Miner : IGameObject
{
    Tunnel* tunnel;
    UniqueTexture mockupLook;
    void mine();
public:
    uint depth = 0;
    std::array<size_t, Material::T_LENGTH> materialsMined {};
    UniqueEvent<uint> mined;
    Miner(Tunnel* tunnel);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget);
};
