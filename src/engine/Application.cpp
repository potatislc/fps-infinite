#include "SDL2/SDL.h"
#include "Application.h"
#include "InputMap.h"

Window Application::window;
Renderer Application::renderer;
AppDebug Application::appDebug;
const uint16_t Application::fps = 60;
float Application::frameTime = 1.f / (float)fps;
float Application::deltaTimeScale = 1.f;
float Application::deltaTime = frameTime * deltaTimeScale;

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

    while (!quit)
    {
        uint64_t frameStart = SDL_GetPerformanceCounter();
        deltaTime = frameTime * deltaTimeScale;

        // Handle events on queue
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
        // appDebug.drawFps(frameCount);
        renderer.render();

        frameCount++;

        // Frame rate cap
        uint64_t frameEnd = SDL_GetPerformanceCounter();
        frameTime = (float)(frameEnd - frameStart) / (float)SDL_GetPerformanceFrequency();
        if (targetFrameTime > frameTime)
        {
            SDL_Delay((uint32_t)((targetFrameTime - frameTime) * 1000.f));
        }
    }
}
