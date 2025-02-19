#pragma once

#include <unordered_map>
#include <SDL.h>
#include <vector>
#include <memory>
#include "engine/entities/IGameObject.h"
#include "engine/utils/Utils.h"

template <typename T>
class StateMachine
{
public:
    class State
    {
    protected:
        T* owner;
        const StateMachine* stateMachine;
    public:
        const char* name;

        State(const char* name, T* owner, StateMachine* stateMachine)
        : name(name), owner(owner), stateMachine(stateMachine) {};
        virtual void enter() {};
        virtual void update() {printf("Base\n");};
        virtual void draw(SDL_Renderer* renderTarget) {};
        virtual void exit() {};
    };

    StateMachine(T* owner, std::vector<std::shared_ptr<State>> states) : owner(owner), states(std::move(states)) {};
    void nextState(uint_t nextStateId)
    {
        if (nextStateId >= states.size()) return;
        states[currentStateId]->exit();
        currentStateId = nextStateId;
        states[currentStateId]->enter();
    }

    std::shared_ptr<State> getCurrentState()
    {
        return states[currentStateId];
    }

    void update()
    {
        states[currentStateId]->update();
    }
    void draw(SDL_Renderer* renderTarget)
    {
        states[currentStateId]->draw(renderTarget);
    }
private:
    T* owner = nullptr;
    uint_t currentStateId = 0;
    std::vector<std::shared_ptr<State>> states;
};