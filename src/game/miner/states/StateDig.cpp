#include "game/Game.h"
#include "game/miner/Miner.h"
#include "engine/InputMap.h"

void Miner::StateDig::update()
{
    Game::mainCam.view.y = (int)std::lerp(Game::mainCam.view.y, 0, 10. * Application::deltaTime);

    if (InputMap::getBoundKeyInput("Dig") == InputMap::S_PRESSED || InputMap::getBoundMouseInput("Dig") == InputMap::S_PRESSED)
    {
        owner->digLayer();
        // Illusion of player movement :O
        Game::mainCam.view.y -= Game::tileSize;
    }
}

void Miner::StateDig::draw(SDL_Renderer *renderTarget)
{
    SDL_Rect source = {0, 0, mockupLook.getSize().x, mockupLook.getSize().y};
    SDL_Rect dest = {Application::renderer.viewport.w / 2 - Game::tileHalfSize, Application::renderer.viewport.h / 2 - Game::tileSize, 31, Game::tileSize * 2};
    SDL_Point origin = {0, 0};
    Game::mainCam.drawTextureEx(mockupLook.get(), &source, &dest, 0.0, &origin, SDL_FLIP_NONE);
}
