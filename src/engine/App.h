#pragma once
#include <cstdint>
#include "Renderer.h"
#include "Window.h"
#include "engine/game_object/IGameObject.h"
#include "AppDebug.h"

class App
{
public:
    static Window window;
    static Renderer renderer;
    static MessageTexture messageTexture;
    static AppDebug appDebug;
    static uint16_t targetFps;
    static double frameTime;
    static uint64_t frameCount;
    static double timeScale;
    static float deltaTime; // Seconds
    static double timeSinceInit; // Seconds
    bool quit = false;
    SDL_Event event{};

    App() = default;
    bool init();
    void run(IGameObject& game);

private:
    bool capFPS = false;
};
