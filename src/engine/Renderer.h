#pragma once
#include <utility>
#include "SDL.h"
#include "engine/utils/Utils.h"

class Renderer
{
public:
    class ViewPortCamera
    {
    public:
        SDL_Renderer* renderTarget = nullptr;
        SDL_Rect viewPort = {0, 0, 0, 0};
        float zoom = 1.f;
        void start(SDL_Renderer* _renderTarget, SDL_Rect _view);
        void drawTexture(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst);
        void drawTextureEx(SDL_Texture *texture, const SDL_Rect *src, SDL_Rect *dst, double angle, const SDL_Point *center, SDL_RendererFlip flip);
    private:
        void viewTransform(SDL_Rect* rect);
    };

    SDL_Renderer* sdlRenderer;
    SDL_Rect viewport;

    const std::pair<uint16_t, uint16_t> viewportDefaultSize = { 256, 256 };
    bool init(SDL_Window* sdlWindow);
    void render() const;

    ~Renderer();
};
