#pragma once

#include "AEntity.h"
#include "engine/utils/Utils.h"

template <typename T>
class EntityScene : public AEntity
{
    static_assert(std::is_base_of<AEntity, T>::value, "T must be derived from AEntity");
public:
    AEntity* parent = nullptr;
    std::vector<std::shared_ptr<T>> children;

    ~EntityScene() = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void addChild(const std::shared_ptr<T>& child);
    void removeChild(T* child);
    size_t getSize();
};

template<typename T>
size_t EntityScene<T>::getSize()
{
    return children.size();
}

template <typename T>
void EntityScene<T>::start()
{
    for (const auto& child : children)
    {
        child->start();
    }
}

template <typename T>
void EntityScene<T>::update()
{
    for (const auto& child : children)
    {
        if (child) child->update();
    }
}

template <typename T>
void EntityScene<T>::draw(SDL_Renderer *renderTarget)
{
    for (const auto& child : children)
    {
        if (child) child->draw(renderTarget);
    }
}

template <typename T>
void EntityScene<T>::addChild(const std::shared_ptr<T>& child)
{
    child->parent = this;
    child->start();
    children.emplace_back(child);
}

template <typename T>
void EntityScene<T>::removeChild(T* child)
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
