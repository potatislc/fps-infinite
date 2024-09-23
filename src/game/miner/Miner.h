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
    static UniqueTexture mockupLook;
    StateMachine<Miner> stateMachine;

    void digLayer();
public:
    uint depth = 0;
    float velocity = 0.f;
    std::array<uint, Material::T_LENGTH> materialsMined {};
    UniqueEvent<uint, Material::Type, uint> dug; // Depth, type, amount

    Miner(Tunnel* tunnel, StateMachine<Miner> stateMachine);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    // States
    enum StateId
    {
        SI_IDLE,
        SI_DIG,
        SI_FALL,
        SI_DEAD,
        SI_LENGTH
    };

    StateMachine<Miner> defaultStateMachine();

    class StateIdle : public StateMachine<Miner>::State
    {
    public:
        StateIdle(const char* name, Miner* owner, StateMachine<Miner>* stateMachine) : StateMachine<Miner>::State(name, owner, stateMachine) {};
    };

    class StateDig : public StateMachine<Miner>::State
    {
        void update() override;
        void draw(SDL_Renderer* renderTarget) override;
    public:
        StateDig(const char* name, Miner* owner, StateMachine<Miner>* stateMachine) : StateMachine<Miner>::State(name, owner, stateMachine) {};
    };

    class StateFall : public StateMachine<Miner>::State
    {
        float gravity = 800.f;
        float maxVelocity = 2000.f;
        int drawingOffset = 0;

        void update() override;
        void draw(SDL_Renderer* renderTarget) override;
    public:
        StateFall(const char* name, Miner* owner, StateMachine<Miner>* stateMachine) : StateMachine<Miner>::State(name, owner, stateMachine) {};
    };

    class StateDead
    {

    };
};
