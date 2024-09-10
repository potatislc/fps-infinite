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
    StateMachine stateMachine;
    void mine();
public:
    uint depth = 0;
    std::array<size_t, Material::T_LENGTH> materialsMined {};
    UniqueEvent<uint> mined;
    Miner(Tunnel* tunnel, StateMachine stateMachine);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    // States
    enum StateId
    {
        SI_DIG,
        SI_IDLE,
        SI_FALL,
        SI_DEAD,
        SI_LENGTH
    };

    StateMachine defaultStateMachine();

    class StateDig : public StateMachine::State
    {
        void update() override;
    public:
        StateDig(const char* name, void* owner, StateMachine* stateMachine) : StateMachine::State(name, owner, stateMachine) {}
    };

    class StateIdle
    {

    };

    class StateFall
    {

    };

    class StateDead
    {

    };
};
