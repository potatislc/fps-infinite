#pragma once
#include <cstdint>
#include "renderer.h"

class Game
{
    const int frameDelay = 1000 / fps;

    void update();

public:
    static const uint16_t fps;
    static float timeScale;
    static float delta;
    bool quit = false;
    SDL_Event e{};

    void run(Renderer renderer);
};
