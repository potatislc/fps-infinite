#pragma once

#include <unordered_map>
#include <SDL.h>
#include "engine/IGameObject.h"

class StateMachine
{
public:
    class State
    {
        void* owner;
        StateMachine* stateMachine{};
    };

    class AGameState : State, IGameObject
    {
        void start() override = 0;
        void update() override = 0;
        void draw(SDL_Renderer* renderTarget) override {};
        virtual void end() {};
    };

    void* owner;
    std::unordered_map<char*, State> states;
    StateMachine(void* owner) : owner(owner) {};
    void AddState(char* name, State state);
};