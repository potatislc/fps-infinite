#include "Renderer.h"
#include "Window.h"

SDL_Renderer* Renderer::sdlRenderer;

bool Renderer::init(SDL_Window* sdlWindow)
{
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    return true;
}

void Renderer::render() const
{
    SDL_RenderPresent(sdlRenderer);
}
