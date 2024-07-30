#include <SDL.h>
#include "engine/Application.h"
#include "game/Game.h"

int main(int argc, char* args[])
{
    {
        Application application;
        Game game;

        if (!application.init()) return -1;
        application.run(game);
    }

    Application::quitSDL();
    return 0;
}
