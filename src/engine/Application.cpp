#include "SDL2/SDL.h"
#include "Application.h"

Window Application::window;
Renderer Application::renderer;
const uint16_t Application::fps = 60;
float Application::timeScale = 1.f;
float Application::delta = 1.f / fps;

bool Application::init()
{
    if (!window.init()) return false;
    if (!renderer.init(window.sdlWindow)) return false;
    return true;
}

void Application::run(IGameObject& game)
{
    game.start();

    while (!quit)
    {
        uint64_t frameStart = SDL_GetTicks();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        game.update();
        game.draw();
        renderer.render();

        // Frame rate cap
        uint64_t frameTime = SDL_GetTicks64() - frameStart;
        delta = ((float)frameTime / 1000) * timeScale;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

Application::~Application()
{
    SDL_DestroyRenderer(renderer.sdlRenderer);
    SDL_DestroyWindow(window.sdlWindow);
    SDL_Quit();
}
