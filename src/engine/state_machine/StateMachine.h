#pragma once

#include <unordered_map>
#include <SDL.h>
#include "engine/IGameObject.h"

class StateMachine
{
    class AState
    {
        void* owner;
        StateMachine* stateMachine{};
    };

    class AGameObjectState : AState, IGameObject
    {
        void start() override = 0;
        void update() override = 0;
        void draw(SDL_Renderer* renderTarget) override {};
    };

    void* owner;
    std::unordered_map<char*, AState> states;
    explicit StateMachine(void* owner) : owner(owner) {};
    void AddState(char* name, AState state);
};