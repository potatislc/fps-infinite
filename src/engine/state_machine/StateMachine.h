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

    class AGameState : State
    {
        virtual void enter() = 0;
        virtual void update() = 0;
        virtual void draw(SDL_Renderer* renderTarget) = 0;
        virtual void exit() = 0;
    };

    void* owner;
    std::unordered_map<char*, State> states;
    StateMachine(void* owner) : owner(owner) {};
    void AddState(char* name, State state);
};