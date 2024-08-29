#include "StateMachine.h"

void StateMachine::AddState(char *name, StateMachine::State state)
{
    states[name] = state;
}
