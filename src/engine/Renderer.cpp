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


void Renderer::Camera::viewTransform(SDL_Rect* rect)
{
    rect->x -= view.x;
    rect->y -= view.y;
}

void Renderer::Camera::drawTexture(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst)
{
    viewTransform(dst);
    SDL_RenderCopy(renderTarget, texture, src, dst);
}

void Renderer::Camera::drawTextureEx(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    viewTransform(dst);
    SDL_RenderCopyEx(renderTarget, texture, src, dst, angle, center, flip);
}

void Renderer::Camera::start(SDL_Renderer *_renderTarget, SDL_Rect _view)
{
    renderTarget = _renderTarget;
    view = _view;
}
