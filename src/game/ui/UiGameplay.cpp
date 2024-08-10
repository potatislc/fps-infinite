#include "UiGameplay.h"
#include "engine/MessageTexture.h"
#include "engine/Application.h"

SDL_Renderer* UiGameplay::sdlRenderer = nullptr;
UniqueTexture UiGameplay::minerDepthMessage;

void UiGameplay::start()
{
    sdlRenderer = Application::renderer.sdlRenderer;
}

void UiGameplay::update()
{

}

void UiGameplay::draw(SDL_Renderer *renderTarget)
{
    if (minerDepthMessage.get() != nullptr)
    {
        SDL_Rect source = {0, 0, minerDepthMessage.getSize().x, minerDepthMessage.getSize().y};
        SDL_Rect dest = {0, 8, minerDepthMessage.getSize().x, minerDepthMessage.getSize().y};
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(renderTarget, minerDepthMessage.get(), &source, &dest, 0.0, &origin, SDL_FLIP_NONE);
    }
}

void UiGameplay::onMinerMined()
{
    printf("I got it!\n");
    minerDepthMessage.set(MessageTexture::messageToTexture(sdlRenderer, MessageTexture::FAI_DEFAULT,
                                                           "Boo!", (SDL_Color){255, 255, 255, 255}));
}


UiGameplay::UiGameplay(Tunnel *tunnel, Miner *miner) : tunnel(tunnel), miner(miner)
{
    miner->mined.setReceiverFunc(onMinerMined);
}
