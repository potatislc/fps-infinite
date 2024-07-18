#include "SDL2/SDL.h"
#include "application.h"

const uint16_t Application::fps = 60;
float Application::timeScale = 1.f;
float Application::delta = 1.f / fps;

void Application::run(Game game, Renderer renderer)
{
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
