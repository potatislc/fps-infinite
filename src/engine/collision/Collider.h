#pragma once

#include <memory>
#include <iostream>
#include <algorithm>
#include "game/Game.h"
#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"
#include "engine/App.h"

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
        float push;
        float spring;
        SoftCollision(float push = 1, float spring = 10) : push(push), spring(spring) {};
        CollisionShape::Hit collide(CollisionShape& myShape, Collider& other) override
        {
            auto hit = myShape.collideWith(*other.shape);

            if (hit)
            {
                *myShape.followPosition += hit.normal * push * App::deltaTime;
                return hit;
            }

            return {};
        };
    };

    struct Hit
    {
        Collider* collider;
        void* owner;
        CollisionShape::Hit data;

        Hit(Collider* collider = nullptr, void* owner = nullptr,
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
    Hit hitRes;

    Collider(id_t id, void* owner, CollisionShape* shape, ICollisionStrategy* strategy, glm::vec3* followPosition) :
            id(id), owner(owner), shape(shape), strategy(strategy)
    {
        shape->followPosition = followPosition;
    };

    template <typename T>
    Hit collideGroup(ColliderGroup<T>& colliderGroup);
    // Checks until first collision
    template <typename T>
    Hit collideGroupNaive(ColliderGroup<T>& colliderGroup);
    bool collideWith(Collider& other);
};

template <typename T>
Collider::Hit Collider::collideGroup(ColliderGroup<T>& colliderGroup)
{
    Collider::Hit lastHit = Collider::Hit();

    for (auto& other : colliderGroup.colliders)
    {
        if ((Collider*)&other == this) continue;

        CollisionShape::Hit hit = strategy->collide(*shape, other);
        if (hit)
        {
            lastHit = Collider::Hit((Collider*)&other, other.owner, hit);
        }
    }

    return lastHit;
}

template<typename T>
Collider::Hit Collider::collideGroupNaive(ColliderGroup<T>& colliderGroup)
{
    for (auto& other : colliderGroup.colliders)
    {
        if ((Collider*)&other == this) continue;
        std::cout << shape->followPosition->x << std::endl;
        std::cout << other.shape->followPosition->x << std::endl;
        CollisionShape::Hit hit = strategy->collide(*shape, other);
        if (hit)
        {
            return Collider::Hit((Collider*)&other, other.owner, hit);
        }
    }

    return Collider::Hit();
}

template <typename OwnerType>
class ColliderGroup
{
public:
    ColliderGroup();
    id_t add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy, glm::vec3* followPosition);
    void populateSpatialGrid();
    void collideAllMembers();
    void queueRemove(id_t colliderId); // Remove at id in the group
    void printSpatialGrid();

    std::vector<Collider> colliders;
    static constexpr int gridWidth = 32;
private:
    class SpatialCell
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

        uint8_t getColliderCount()
        {
            return colliderCount;
        }

        static constexpr uint8_t maxColliderCount = UINT8_MAX;
        uint8_t colliderCount = 0;
        std::array<id_t, maxColliderCount> collidersInside = {0};
    };

    // There is a difference between map cells and spatial grid cells sadly ;(. #badatnamingstuff
    const float cellWidth = Game::maxCellSize.x / gridWidth;

    std::array<SpatialCell, gridWidth * gridWidth> spatialGrid;
};

template<typename OwnerType>
void ColliderGroup<OwnerType>::printSpatialGrid()
{
    std::cout << "Spatial Grid" << std::endl;
    for (int i = 0; i < spatialGrid.size(); i++)
    {
        std::cout << static_cast<int>(spatialGrid[i].getColliderCount()) << " ";
        if ((i + 1) % gridWidth == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename OwnerType>
ColliderGroup<OwnerType>::ColliderGroup()
{

}

template<typename OwnerType>
void ColliderGroup<OwnerType>::collideAllMembers()
{
    for (auto& cell : spatialGrid)
    {
        int colliderCount = cell.getColliderCount();
        if (colliderCount < 2) continue;

        for (int i = 0; i < colliderCount; ++i)
        {
            for (int j = i+1; j < colliderCount; ++j)
            {
                // if (i == j) continue;
                uint_t thisId = cell.collidersInside[i];
                uint_t otherId = cell.collidersInside[j];
                if (colliders[thisId].collideWith(colliders[otherId])) continue;
            }
        }
    }
}

template<typename OwnerType>
void ColliderGroup<OwnerType>::populateSpatialGrid()
{
    for (auto& cell : spatialGrid)
    {
        cell.resetCount();
    }

    bool forward = (App::frameCount % 2 == 0);
    int start = forward ? 0 : colliders.size() - 1;
    int end = forward ? colliders.size() : -1;
    int step = forward ? 1 : -1;

    for (int i = start; i != end; i += step)
    {
        auto& collider = colliders[i];
        collider.shape->computeTouchingCells(gridWidth, cellWidth);
        for (int j = 0; j < collider.shape->touchingCells.index; j++)
        {
            spatialGrid[collider.shape->touchingCells.array[j]].addCollider(collider.id);
        }
    }
}

template<typename OwnerType>
void ColliderGroup<OwnerType>::queueRemove(id_t colliderId)
{

}

template<typename OwnerType>
id_t ColliderGroup<OwnerType>::add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy, glm::vec3* followPosition)
{
    id_t nextId = colliders.size();
    colliders.emplace_back(nextId, owner, shape, strategy, followPosition);
    return nextId;
}