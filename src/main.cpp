#include <SDL.h>
#include "engine/App.h"
#include "game/Game.h"

int main(int argc, char* args[])
{
    {
        App app = App();
        Game game = Game();

        if (!app.init()) return -1;
        app.run(game);
        // SDL_SetWindowFullscreen(App::window.sdlWindow, 0);
        SDL_DestroyRenderer(App::renderer.sdlRenderer);
        SDL_DestroyWindow(App::window.sdlWindow);
    }

    SDL_Quit();
    return 0;
}
