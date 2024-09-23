#include "SDL2/SDL.h"
#include "Application.h"
#include "InputMap.h"

Window Application::window;
Renderer Application::renderer;
AppDebug Application::appDebug;
uint16_t Application::targetFps = 60;
double Application::frameTime = 1. / (double)targetFps;
double Application::timeScale = 1.;
double Application::deltaTime = frameTime * timeScale;

bool Application::init()
{
    if (!window.init()) return false;
    if (!renderer.init(window.sdlWindow)) return false;
    TTF_Init();
    MessageTexture::loadFontAtlases();
    appDebug.init();
    return true;
}

void Application::run(IGameObject& game)
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
        currentTime = SDL_GetPerformanceCounter();
        deltaTime = ((double)(currentTime - lastTime) / performanceFrequency) * timeScale;
        lastTime = currentTime;

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            if (InputMap::keyMap.count(event.key.keysym.sym))
            {
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        InputMap::keyMap[event.key.keysym.sym] = true;
                        break;

                    case SDL_KEYUP:
                        InputMap::keyMap[event.key.keysym.sym] = false;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        InputMap::mouseMap[event.button.button] = true;
                        break;

                    case SDL_MOUSEBUTTONUP:
                        InputMap::mouseMap[event.button.button] = false;
                        break;

                    default:
                        break;
                }
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