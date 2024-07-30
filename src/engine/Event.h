#pragma once

#include <vector>

class IEvent
{
    virtual void send() {};
};

class UniqueEvent : IEvent
{
    void (*receiverFunc)();
public:
    void setReceiverFunc(void (*func)());
    void send() override;
};

class SharedEvent : IEvent
{
    std::vector<void(*)()> receiverFuncs;
public:
    void addReceiverFunc(void (*func)());
    void send() override;
};