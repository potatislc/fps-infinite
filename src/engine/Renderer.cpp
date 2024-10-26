#include "Renderer.h"
#include "App.h"

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
                             App::window.width * viewport.w / App::window.width,
                             App::window.height * viewport.h / App::window.height);
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


void Renderer::ViewPortCamera::viewTransform(SDL_Rect* rect)
{
    rect->x -= viewPort.x;
    rect->y -= viewPort.y;
}

void Renderer::ViewPortCamera::drawTexture(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst)
{
    viewTransform(dst);
    SDL_RenderCopy(renderTarget, texture, src, dst);
}

void Renderer::ViewPortCamera::drawTextureEx(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    viewTransform(dst);
    SDL_RenderCopyEx(renderTarget, texture, src, dst, angle, center, flip);
}

void Renderer::ViewPortCamera::start(SDL_Renderer *_renderTarget, SDL_Rect _view)
{
    renderTarget = _renderTarget;
    viewPort = _view;
}
