#pragma once
#include "game/miner/Miner.h"
#include "Tunnel.h"
#include "engine/IGameObject.h"
#include "SDL_render.h"
#include "game/ui/UiGameplay.h"
#include "engine/Renderer.h"
#include "engine/Application.h"

class Game : public IGameObject
{
    void clearBackground(SDL_Renderer* renderTarget);
    void drawDebugGrid(SDL_Renderer* renderTarget);
public:
    static const uint8_t tileSize = 32;
    static const uint8_t tileHalfSize = tileSize / 2;
    static uint8_t tileCountX;
    static uint8_t tileCountY;
    static Renderer::Camera mainCam;
    Tunnel tunnel;
    Miner miner = {&tunnel, miner.defaultStateMachine()};
    UiGameplay uiGameplay = {&tunnel, &miner};

    Game();
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};
