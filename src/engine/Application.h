#pragma once
#include <cstdint>
#include "Renderer.h"
#include "Window.h"
#include "IGameObject.h"
#include "AppDebug.h"

class Application
{
    float targetFrameTime = 1.f / (float)fps;
    uint64_t frameCount = 0;
public:
    static Window window;
    static Renderer renderer;
    static AppDebug appDebug;
    static const uint16_t fps;
    static float frameTime;
    static float deltaTimeScale;
    static float deltaTime;
    bool quit = false;
    SDL_Event event{};

    bool init();
    void run(IGameObject& game);
};
