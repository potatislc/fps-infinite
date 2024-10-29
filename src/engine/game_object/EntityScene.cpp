#include "EntityScene.h"

void EntityScene::start()
{
    for (const auto& child : children)
    {
        child->start();
    }
}

void EntityScene::update()
{
    for (const auto& child : children)
    {
        if (child) child->update();
    }
}

void EntityScene::draw(SDL_Renderer *renderTarget)
{
    for (const auto& child : children)
    {
        if (child) child->draw(renderTarget);
    }
}

void EntityScene::addChild(const std::shared_ptr<AEntity>& child)
{
    child->parent = this;
    child->start();
    children.emplace_back(child);
}

void EntityScene::removeChild(AEntity* child)
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if (it->get() == child)
        {
            children.erase(it);
            return;
        }
    }
}
