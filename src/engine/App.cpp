#include "SDL2/SDL.h"
#include "App.h"
#include "InputMap.h"
#include "glm/glm.hpp"

Window App::window;
Renderer App::renderer;
AppDebug App::appDebug;
uint16_t App::targetFps = 60;
double App::frameTime = 1. / (double)targetFps;
uint64_t App::frameCount = 0;
double App::timeScale = 1.;
float App::deltaTime = (float)(frameTime * timeScale);
double App::timeSinceInit = 0;

bool App::init()
{
    if (!window.init()) return false;
    if (!renderer.init(window.sdlWindow)) return false;
    // TTF_Init();
    MessageTexture::loadFontAtlases();
    appDebug.init();
    return true;
}

void App::run(IGameObject& game)
{
    game.start();

    uint64_t lastTime = SDL_GetPerformanceCounter();
    uint64_t currentTime;
    auto performanceFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    double frameDelay = 1000. / targetFps;
    uint64_t frameStart;

    while (!quit)
    {
        frameStart = SDL_GetPerformanceCounter();
        deltaTime = (float)(((double)(frameStart - lastTime) / performanceFrequency) * timeScale);
        timeSinceInit += deltaTime;
        lastTime = frameStart;

        int mouseX, mouseY;
        SDL_GetRelativeMouseState(&mouseX, &mouseY);
        InputMap::mouseMotion = {mouseX, mouseY};
        SDL_GetMouseState(&mouseX, &mouseY);
        InputMap::mousePosition = {mouseX, mouseY};

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                if (InputMap::keyMap.count(event.key.keysym.sym))
                {
                    InputMap::keyMap[event.key.keysym.sym] = (event.type == SDL_KEYDOWN);
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
            {
                InputMap::mouseMap[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN);
            }
        }

        game.update();
        game.draw(renderer.sdlRenderer);
        frameCount++;
        appDebug.drawAvgFps(frameCount);
        renderer.render();

        frameTime = (double)(SDL_GetPerformanceCounter() - frameStart) * 1000 / (double)SDL_GetPerformanceFrequency();
        if (frameTime < frameDelay && capFPS)
        {
            SDL_Delay((uint32_t)(frameDelay - frameTime));
        }
    }
}