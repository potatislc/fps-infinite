#pragma once

#include <memory>
#include <vector>
#include "SDL_render.h"

#include "engine/IGameObject.h"

class ASceneObject;

class GameScene : IGameObject
{
    std::vector<ASceneObject*> children;
public:
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void addChild(ASceneObject* child);
    void removeChild(ASceneObject* child);
};

class ASceneObject : IGameObject
{
public:
    GameScene* parent;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderTarget) = 0;
    void queueFree();
};
