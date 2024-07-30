#include <cstdio>
#include "Event.h"

void UniqueEvent::setReceiverFunc(void (*func)())
{
    receiverFunc = func;
}

void UniqueEvent::send()
{
    if (receiverFunc == nullptr)
    {
        printf("EVENT SEND FAILED: Receiver function not set.");
        return;
    }
    // TODO: ERROR HANDLING FOR WRONG NUMBER OF ARGUMENTS
    receiverFunc();
}

void SharedEvent::addReceiverFunc(void (*func)())
{
    receiverFuncs.push_back(func);
}

void SharedEvent::send()
{

}
