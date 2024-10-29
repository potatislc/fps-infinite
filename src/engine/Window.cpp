#include "Window.h"

Window::Window()
{
    width = 426;
    height = 240;
    centerW = floor(Window::width / 2);
    centerH = floor(Window::height / 2);
}

bool Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    sdlWindow = SDL_CreateWindow("Dig Straight Down!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    return true;
}

Window::~Window()
{
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}
