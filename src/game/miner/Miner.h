#pragma once

#include <cstdio>
#include <array>
#include "game/Tunnel.h"
#include "engine/IGameObject.h"
#include "SDL_render.h"
#include "engine/Event.h"
#include "engine/state_machine/StateMachine.h"

class Miner : IGameObject
{
    Tunnel* tunnel;
    UniqueTexture mockupLook;
    StateMachine stateMachine = {this};
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
