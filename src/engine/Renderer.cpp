#include "Renderer.h"
#include "Application.h"

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

    viewport = (SDL_Rect){ 0, 0, viewportDefaultSize.first, viewportDefaultSize.second };
    SDL_RenderSetViewport(sdlRenderer, &viewport);
    // SDL_RenderSetScale(sdlRenderer, Application::window.width / viewport.w, Application::window.height / viewport.h);
    SDL_RenderSetLogicalSize(sdlRenderer,
                             Application::window.width * viewport.w / Application::window.width,
                             Application::window.height * viewport.h / Application::window.height);
    return true;
}

void Renderer::render() const
{
    SDL_RenderPresent(sdlRenderer);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(sdlRenderer);
}
