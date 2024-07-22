#pragma once
#include <cstdint>
#include "Renderer.h"
#include "Window.h"
#include "IGameObject.h"

class Application
{
    const int frameDelay = 1000 / fps;

public:
    static Window window;
    static Renderer renderer;
    static const uint16_t fps;
    static float timeScale;
    static float delta;
    bool quit = false;
    SDL_Event event{};

    ~Application();
    bool init();
    void run(IGameObject& game);
};
