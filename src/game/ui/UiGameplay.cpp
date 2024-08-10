#include "UiGameplay.h"

void UiGameplay::start()
{

}

void UiGameplay::update()
{

}

void UiGameplay::draw(SDL_Renderer *renderTarget)
{

}

void UiGameplay::onMinerMined()
{
    printf("I got it!\n");
}


UiGameplay::UiGameplay(Tunnel *tunnel, Miner *miner) : tunnel(tunnel), miner(miner)
{
    miner->mined.setReceiverFunc(onMinerMined);
}
