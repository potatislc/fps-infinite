#include "UiGameplay.h"
#include "engine/MessageTexture.h"
#include "engine/Application.h"
#include "game/Game.h"

SDL_Renderer* UiGameplay::sdlRenderer = nullptr;
UniqueTexture UiGameplay::minerDepthMessage;
std::stringstream UiGameplay::minerDepthText;
std::array<UniqueTexture, Material::T_LENGTH> UiGameplay::materialsMinedMessage;

void UiGameplay::start()
{
    sdlRenderer = Application::renderer.sdlRenderer;
    onMinerDug(0, Material::T_AIR, 0);
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

    const int margin = 8;
    int offsetX = Game::mainCam.view.w;
    for (uint i = 1; i < Material::T_LENGTH; i++)
    {
        if (materialsMinedMessage[i].get() != nullptr)
        {
            offsetX -= materialsMinedMessage[i].getSize().x + margin;
            SDL_Rect source = {0, 0, materialsMinedMessage[i].getSize().x, materialsMinedMessage[i].getSize().y};
            SDL_Rect dest = {offsetX, 8, materialsMinedMessage[i].getSize().x, materialsMinedMessage[i].getSize().y};
            SDL_Point origin = {0, 0};
            SDL_RenderCopyEx(renderTarget, materialsMinedMessage[i].get(), &source, &dest, 0.0, &origin, SDL_FLIP_NONE);
        }
    }
}

void UiGameplay::onMinerDug(uint depth, Material::Type type, uint materialAmount)
{
    minerDepthText.str("");
    minerDepthText << depth << "m";
    minerDepthMessage.set(MessageTexture::messageToTexture(sdlRenderer, MessageTexture::FAI_DEFAULT,
                                                           minerDepthText.str().c_str(), (SDL_Color){255, 255, 255, 255}));
    materialsMinedMessage[type].set(
            MessageTexture::messageToTexture(sdlRenderer, MessageTexture::FAI_DEFAULT, std::to_string(materialAmount).c_str(), (SDL_Color){255, 255, 255, 255}));
}

UiGameplay::UiGameplay(Tunnel *tunnel, Miner *miner) : tunnel(tunnel)
{
    miner->dug.setReceiverFunc(onMinerDug);
}
