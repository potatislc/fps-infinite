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

    bool collideWith(Collider& other);
};

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
    static constexpr int gridWidth = 96;
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

        static inline constexpr uint8_t maxColliderCount = 8;
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
        std::cout << static_cast<int>(spatialGrid[i].getColliderCount());
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

        for (int i = 0; i < colliderCount - 1; ++i)
        {
            Collider& current = colliders[cell.collidersInside[i]];
            for (int j = i+1; j < colliderCount; ++j)
            {
                Collider& other = colliders[cell.collidersInside[j]];
                if (current.collideWith(other)) continue;
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

    for (auto& collider: colliders)
    {
        auto& shape = collider.shape;
        shape->computeTouchingCells(gridWidth, cellWidth);
        for (int j = 0; j < shape->touchingCells.size; j++)
        {
            spatialGrid[shape->touchingCells.array[j]].addCollider(collider.id);
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