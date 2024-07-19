#include <SDL.h>
#include "engine/Window.h"
#include "engine/Application.h"
#include "engine/Renderer.h"
#include "game/Game.h"

Window window;
Application application;
Game game;
Renderer renderer;

int main(int argc, char* args[])
{
    if (!window.init()) return -1;
    if (!renderer.init(window.sdlWindow)) return -1;
    application.run(game, renderer);

    SDL_DestroyRenderer(renderer.sdlRenderer);
    SDL_DestroyWindow(window.sdlWindow);
    SDL_Quit();

    return 0;
}
