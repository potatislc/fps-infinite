#include "StateMachine.h"

StateMachine::StateMachine(void *owner, std::vector<std::shared_ptr<State>> states) : owner(owner), states(std::move(states))
{

}

void StateMachine::nextState(uint nextStateId)
{
    if (nextStateId >= states.size()) return;
    states[currentStateId]->exit();
    currentStateId = nextStateId;
    states[currentStateId]->enter();
}

void StateMachine::update()
{
    states[currentStateId]->update();
}

void StateMachine::draw(SDL_Renderer *renderTarget)
{
    states[currentStateId]->draw(renderTarget);
}
