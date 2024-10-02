#pragma once

#include <memory>
#include <vector>
#include "SDL_render.h"
#include "engine/IGameObject.h"

class GameScene : IGameObject
{
    std::vector<std::shared_ptr<IGameObject>> gameObjects;
public:
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void addGameObject(IGameObject* gameObject);
    void removeGameObject(IGameObject* gameObject);
};
