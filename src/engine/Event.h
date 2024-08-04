#pragma once

#include <vector>

template <typename... ReceiverArgs>
class AEvent
{
public:
    virtual void send(ReceiverArgs... receiverArgs) {};
};

template <typename... ReceiverArgs>
class UniqueEvent : public AEvent<ReceiverArgs...>
{
    void (*receiverFunc)(ReceiverArgs...);
public:
    void setReceiverFunc(void (*func)(ReceiverArgs...), ReceiverArgs... receiverArgs)
    {
        receiverFunc = func;
    }

    void send(ReceiverArgs... receiverArgs) override
    {
        receiverFunc(receiverArgs...);
    }
};

/*
template <typename... Args> class SharedEvent : AEvent<>
{
    std::vector<void(*)()> receiverFuncs;
public:
    void addReceiverFunc(void (*func)());
    void send() override;
};
*/