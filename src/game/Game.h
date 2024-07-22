#pragma once
#include "Miner.h"
#include "Tunnel.h"
#include "engine/IGameObject.h"
#include "SDL_render.h"

class Game : public IGameObject
{
    void clearBackground(SDL_Renderer* renderTarget);
    void drawDebugGrid(SDL_Renderer* renderTarget);
public:
    static const uint8_t tileSize = 32;
    static const uint8_t tileHalfSize = tileSize / 2;
    static uint16_t tilesW;
    static uint16_t tilesH;
    Tunnel tunnel;
    Miner miner = { &tunnel };

    Game();
    void start() override;
    void update() override;
    void draw() override;
};
