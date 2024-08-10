#pragma once

#include <SDL.h>
#include "engine/IGameObject.h"
#include "game/Miner.h"

class UiGameplay : IGameObject
{
    Tunnel* tunnel;
    Miner* miner;
    static SDL_Renderer* sdlRenderer;
    static UniqueTexture minerDepthMessage;
    static void onMinerMined();
public:
    UiGameplay(Tunnel* tunnel, Miner* miner);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};
