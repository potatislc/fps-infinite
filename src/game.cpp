#include <SDL.h>
#include "game.h"

const uint16_t Game::fps = 60;
float Game::timeScale = 1.f;
float Game::delta = 1.f/fps;

void Game::update()
{

}

void Game::run(Renderer renderer)
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

        update();
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
