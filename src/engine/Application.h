#pragma once
#include <cstdint>
#include "Renderer.h"
#include "Window.h"
#include "IGameObject.h"
#include "AppDebug.h"

class Application
{
    uint64_t frameCount = 0;
    bool capFPS = true;
public:
    static Window window;
    static Renderer renderer;
    static MessageTexture messageTexture;
    static AppDebug appDebug;
    static uint16_t targetFps;
    static double frameTime;
    static double timeScale;
    static double deltaTime;
    bool quit = false;
    SDL_Event event{};

    Application() = default;
    bool init();
    void run(IGameObject& game);
};
