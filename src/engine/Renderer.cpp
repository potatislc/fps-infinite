#include "Renderer.h"
#include "Window.h"

SDL_Renderer* currentRenderer;

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

    currentRenderer = sdlRenderer;

    return true;
}

void Renderer::render() const
{
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);

    // Temporary ---
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 255);
    SDL_Rect fillRect = { Window::screenWidth / 4, Window::screenHeight / 4, Window::screenWidth / 2, Window::screenHeight / 2 };
    SDL_RenderFillRect(sdlRenderer, &fillRect);
    // ---

    SDL_RenderPresent(sdlRenderer);
}
