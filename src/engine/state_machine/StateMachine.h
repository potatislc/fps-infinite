#pragma once

#include <unordered_map>
#include <SDL.h>
#include <vector>
#include <memory>
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
        virtual void enter() {};
        virtual void update() {};
        virtual void draw(SDL_Renderer* renderTarget) {};
        virtual void exit() {};
    };

    StateMachine(void* owner, std::vector<std::shared_ptr<State>> states);
    void nextState(uint nextStateId);
    void update();
    void draw(SDL_Renderer* renderTarget);
private:
    void* owner = nullptr;
    uint currentStateId = 0;
    std::vector<std::shared_ptr<State>> states;
};