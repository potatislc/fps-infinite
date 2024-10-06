#include "engine/GameScene.h"

void GameScene::start()
{
    for (const auto& child : children)
    {
        child->start();
    }
}

void GameScene::update()
{
    for (const auto& child : children)
    {
        if (child != nullptr) child->update();
    }
}

void GameScene::draw(SDL_Renderer *renderTarget)
{
    for (const auto& child : children)
    {
        if (child != nullptr) child->draw(renderTarget);
    }
}

void GameScene::addChild(ASceneObject* child)
{
    child->parent = this;
    children.emplace_back(child);
    child->start();
}

void GameScene::removeChild(ASceneObject* child)
{
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == child)
        {
            children.erase(children.begin() + i);
            return;
        }
    }
}

void ASceneObject::queueFree() {
    if (parent != nullptr) parent->removeChild(this);
    delete this;
}
