#include <SDL.h>
#include "engine/Application.h"
#include "game/Game.h"
#include "engine/InputMap.h"

Application application;
Game game;

int main(int argc, char* args[])
{
    if (!application.init()) return -1;
    application.run(game);

    return 0;
}
