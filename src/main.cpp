#include <SDL.h>
#include "engine/App.h"
#include "game/Game.h"

int main(int argc, char* args[])
{
    App app = App();
    Game game = Game();

    if (!app.init()) return -1;
    app.run(game);
    return 0;
}
