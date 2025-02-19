#pragma once

#include <memory>
#include <iostream>
#include "game/Game.h"
#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"

class Collider;

template <typename OwnerType>
class ColliderGroup;

class Collider
{
public:
    class ICollisionStrategy
    {
    public:
        virtual CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) = 0;
    };

    class TriggerCollision : public ICollisionStrategy
    {
    public:
        CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) override
        {
            return myShape.collideWith(*other.shape);
        };
    };

    class SolidCollision : public ICollisionStrategy
    {
    public:
        CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) override
        {
            auto hit = myShape.collideWith(*other.shape);

            if (hit)
            {
                *(myShape.followPosition) = *(other.shape->followPosition) + hit.normal * hit.distThreshold;
                return hit;
            }

            return {};
        };
    };

    class SolidCollision2D : public ICollisionStrategy
    {
    public:
        CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) override
        {
            auto hit = myShape.collideWith(*other.shape);

            if (hit)
            {
                *(myShape.followPosition) = glm::vec3(other.shape->followPosition->x, other.shape->followPosition->y, myShape.followPosition->z) + hit.normal * hit.distThreshold;
                return hit;
            }

            return {};
        };
    };

    class SoftCollision : public ICollisionStrategy
    {
    public:
        float push = 0;
        float spring = 0;
        CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) override
        {

            return {};
        };
    };

    template <typename T>
    struct Hit
    {
        Collider* collider;
        T* owner;
        CollisionShape::Hit data;

        Hit(Collider* collider = nullptr, T* owner = nullptr,
            CollisionShape::Hit data = CollisionShape::Hit()) :
                collider(collider), owner(owner), data(data) {};

        explicit operator bool() const
        {
            return collider;
        }
    };

    id_t id = 0;
    void* owner = nullptr;
    CollisionShape* shape;
    ICollisionStrategy* strategy;
    CollisionShape::Hit hitRes;

    Collider(id_t id, void* owner, CollisionShape* shape, ICollisionStrategy* strategy, glm::vec3* followPosition) :
            id(id), owner(owner), shape(shape), strategy(strategy)
    {
        shape->followPosition = followPosition;
    };

    template <typename T>
    Hit<T> collideGroup(ColliderGroup<T>& colliderGroup);
    // Checks until first collision
    template <typename T>
    Hit<T> collideGroupNaive(ColliderGroup<T>& colliderGroup);
};

template <typename T>
Collider::Hit<T> Collider::collideGroup(ColliderGroup<T>& colliderGroup)
{
    Collider::Hit<T> lastHit = Collider::Hit<T>();

    for (auto& other : colliderGroup.colliders)
    {
        if ((Collider*)&other == this) continue;

        CollisionShape::Hit hit = strategy->collide(*shape, other);
        if (hit)
        {
            lastHit = Collider::Hit<T>((Collider*)&other, static_cast<T*>(other.owner), hit);
        }
    }

    return lastHit;
}

template<typename T>
Collider::Hit<T> Collider::collideGroupNaive(ColliderGroup<T>& colliderGroup)
{
    for (auto& other : colliderGroup.colliders)
    {
        if ((Collider*)&other == this) continue;
        std::cout << shape->followPosition->x << std::endl;
        std::cout << other.shape->followPosition->x << std::endl;
        CollisionShape::Hit hit = strategy->collide(*shape, other);
        if (hit)
        {
            return Collider::Hit<T>((Collider*)&other, static_cast<T*>(other.owner), hit);
        }
    }

    return Collider::Hit<T>();
}

template <typename OwnerType>
class ColliderGroup
{
public:
    id_t add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy, glm::vec3* followPosition);
    void populateSpatialGrid();
    void collideAll();
    void queueRemove(id_t colliderId); // Remove at id in the group

    std::vector<Collider> colliders;
private:
    class spatialCell
    {
    public:
        void addCollider(id_t colliderId)
        {
            if (colliderCount >= maxColliderCount) return;
            collidersInside[colliderCount] = colliderId;
            colliderCount++;
        }

        // We don't need to clear the array
        void resetCount()
        {
            colliderCount = 0;
        }
    private:
        typedef uint8_t count_t;
        static constexpr count_t maxColliderCount = 8;
        std::array<id_t, maxColliderCount> collidersInside;
        count_t colliderCount = 0;
    };

    static constexpr size_t gridWidth = 16;
    // There is a difference between map cells and spatial grid cells sadly ;(. #badatnamingstuff
    const float cellWidth = Game::maxCellSize.x / gridWidth;

    std::array<spatialCell, gridWidth * gridWidth> spatialGrid;
};

template<typename OwnerType>
void ColliderGroup<OwnerType>::collideAll()
{
    for (auto& cell : spatialGrid)
    {
        // Collision
    }
}

template<typename OwnerType>
void ColliderGroup<OwnerType>::queueRemove(id_t colliderId)
{

}

template<typename OwnerType>
void ColliderGroup<OwnerType>::populateSpatialGrid()
{
    // Clear spatial grid
    for (auto& cell : spatialGrid)
    {
        cell.resetCount();
    }

    for (auto& collider : colliders)
    {
        // Add collider to touching cells
        // We start by adding to one cell for simplicity
        SDL_Point cell{static_cast<int>(collider.shape->followPosition->x / cellWidth),
                       static_cast<int>(collider.shape->followPosition->y / cellWidth)};
        spatialGrid[cell.y * gridWidth + cell.x].addCollider(collider.id);
    }
}

template<typename OwnerType>
id_t ColliderGroup<OwnerType>::add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy, glm::vec3* followPosition)
{
    id_t nextId = colliders.size();
    colliders.emplace_back(nextId, owner, shape, strategy, followPosition);
    return nextId;
}