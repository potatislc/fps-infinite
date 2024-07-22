#include "Window.h"

uint16_t Window::width = 512;
uint16_t Window::height = 512;
uint16_t Window::centerW = floor(Window::width / 2);
uint16_t Window::centerH = floor(Window::height / 2);

bool Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    sdlWindow = SDL_CreateWindow("Dig Straight Down!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
