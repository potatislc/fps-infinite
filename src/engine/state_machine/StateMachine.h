#pragma once

#include <unordered_map>
#include <SDL.h>
#include <vector>
#include "engine/IGameObject.h"
#include "engine/utils/Utils.h"

class StateMachine
{
public:
    class State
    {
    protected:
        void* owner;
        const StateMachine* stateMachine;
    public:
        const char* name;

        State(const char* name, void* owner, StateMachine* stateMachine)
        : name(name), owner(owner), stateMachine(stateMachine) {};
        virtual void enter() const {};
        virtual void update() const {};
        virtual void draw(SDL_Renderer* renderTarget) const {};
        virtual void exit() const {};
    };

    StateMachine(void* owner, std::vector<State> states);
    void nextState(uint nextStateId);
    void update();
    void draw(SDL_Renderer* renderTarget);
private:
    void* owner = nullptr;
    uint currentStateId = 0;
    const std::vector<State> states;
};