#pragma once

#include <SDL.h>
#include <sstream>
#include "engine/IGameObject.h"
#include "game/Miner.h"

class UiGameplay : IGameObject
{
    Tunnel* tunnel;
    Miner* miner;
    static SDL_Renderer* sdlRenderer;
    static std::stringstream minerDepthText;
    static UniqueTexture minerDepthMessage;
    static void onMinerMined(uint depth);
public:
    UiGameplay(Tunnel* tunnel, Miner* miner);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};
