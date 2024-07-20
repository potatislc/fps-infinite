#pragma once
#include "Miner.h"
#include "Tunnel.h"
#include "engine/IGameObject.h"
#include "SDL_render.h"

class Game : public IGameObject
{
    void clearBackground(SDL_Renderer* renderTarget);

public:
    Tunnel tunnel;
    Miner miner = { &tunnel };
    Game();
    void start() override;
    void update() override;
    void draw() override;
};
