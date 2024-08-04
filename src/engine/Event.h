#pragma once

#include <vector>

template <typename... Args> class AEvent
{
    std::tuple<Args...> receiverArgs;
public:
    explicit AEvent(Args... receiverArgs) : receiverArgs(std::make_tuple(receiverArgs...)) {}
    virtual void send() {};
};

template <typename... Args> class UniqueEvent : AEvent<>
{
    void (*receiverFunc)();
public:
    void setReceiverFunc(void (*func)());
    void send() override;
};

template <typename... Args> class SharedEvent : AEvent<>
{
    std::vector<void(*)()> receiverFuncs;
public:
    void addReceiverFunc(void (*func)());
    void send() override;
};