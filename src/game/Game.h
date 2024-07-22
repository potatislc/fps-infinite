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
    static uint8_t tileCountX;
    static uint8_t tileCountY;
    Tunnel tunnel;
    Miner miner = { &tunnel };

    void start() override;
    void update() override;
    void draw() override;
};
