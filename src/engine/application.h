#pragma once
#include <cstdint>
#include "renderer.h"
#include "../game/game.h"

class Application
{
    const int frameDelay = 1000 / fps;

    void update();

public:
    static const uint16_t fps;
    static float timeScale;
    static float delta;
    bool quit = false;
    SDL_Event e{};

    void run(Game game, Renderer renderer);
};
