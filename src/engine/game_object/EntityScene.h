#pragma once


#include <unordered_set>
#include "AEntity.h"
#include "engine/utils/Utils.h"

template <typename T>
class EntityScene : public AEntity
{
    static_assert(std::is_base_of<AEntity, T>::value, "T must be derived from AEntity");
public:
    AEntity* parent = nullptr;
    std::vector<std::shared_ptr<T>> children;
    std::vector<std::shared_ptr<T>> addQueue;
    std::unordered_set<T*> removalQueue;

    ~EntityScene() = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void queueAddChild(const std::shared_ptr<T>& child);
    void queueRemoveChild(T* child);
    void addAllFromQueue();
    void clearRemovalQueue();
    size_t getSize();
};

template<typename T>
void EntityScene<T>::addAllFromQueue()
{
    children.reserve(children.size() + addQueue.size());

    for (auto& toAdd : addQueue)
    {
        children.push_back(std::move(toAdd));
    }

    addQueue.clear();
}

template<typename T>
void EntityScene<T>::clearRemovalQueue()
{
    if (removalQueue.empty()) return;

    auto it = children.begin();
    while (it != children.end())
    {
        if (removalQueue.contains(it->get()))
        {
            it = children.erase(it);
            removalQueue.erase(it->get());
            if (removalQueue.empty()) return;
        }
        else
        {
            ++it;
        }
    }
}

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
void EntityScene<T>::queueAddChild(const std::shared_ptr<T>& child)
{
    child->parent = this;
    child->start();
    children.emplace_back(child);
    // addQueue.emplace_back(child);
}

template <typename T>
void EntityScene<T>::queueRemoveChild(T* child)
{
    removalQueue.emplace(child);
}
