#include <cmath>
#include "game/miner/Miner.h"
#include "game/Game.h"

void Miner::StateFall::update()
{
    owner->velocity = fminf(owner->velocity + gravity * (float)Application::deltaTime, maxVelocity);
    drawingOffset += static_cast<int>(owner->velocity * Application::deltaTime);

    if (owner->tunnel->layers[owner->tunnel->floorLayerIndex].materialType == Material::T_AIR)
    {
        if (drawingOffset >= Game::tileSize)
        {
            owner->digLayer();
            drawingOffset -= Game::tileSize;
        }
    }
    else
    {
        owner->velocity = 0.f;
        owner->stateMachine.nextState(Miner::SI_DIG);
    }

    Game::mainCam.view.y = drawingOffset;
}

void Miner::StateFall::draw(SDL_Renderer *renderTarget)
{
    SDL_Rect source = {0, 0, mockupLook.getSize().x, mockupLook.getSize().y};
    SDL_Rect dest = {Application::renderer.viewport.w / 2 - Game::tileHalfSize, Application::renderer.viewport.h / 2 - Game::tileSize + drawingOffset, 31, Game::tileSize * 2};
    Game::mainCam.drawTexture(mockupLook.get(), &source, &dest);
}