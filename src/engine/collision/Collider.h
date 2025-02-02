#pragma once

#include <memory>
#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"
#include "game/characters/Player.h"
#include "game/characters/Eye.h"

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

            if (hit == true)
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

            if (hit == true)
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

    id_t id = 0;
    void* owner = nullptr;
    CollisionShape* shape;
    ICollisionStrategy* strategy;

    Collider(id_t id, void* owner, CollisionShape* shape, ICollisionStrategy* strategy, glm::vec3* followPosition) :
            id(id), owner(owner), shape(shape), strategy(strategy)
    {
        shape->followPosition = followPosition;
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

        bool operator==(bool)
        {
            return collider;
        }
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
        if (hit == true)
        {
            lastHit = Collider::Hit<T>((Collider*)&other, static_cast<T*>(other.owner), hit);
        }
    }

    return lastHit;
}

template<typename T>
Collider::Hit<T> Collider::collideGroupNaive(ColliderGroup<T>& colliderGroup)
{
    /*
     * Optimization time!
     * Temporary vector of colliders. Colliders that don't collide with anyone should be popped of the list.
     * The collider you collide with should also be popped of the list.
     * Reserve space for the temp-vector with the size of the original vector.
     */

    for (auto& other : colliderGroup.colliders)
    {
        if ((Collider*)&other == this) continue;

        CollisionShape::Hit hit = strategy->collide(*shape, other);
        if (hit == true)
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
    void add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy, glm::vec3* followPosition);

    std::vector<Collider> colliders;
};

template<typename OwnerType>
void ColliderGroup<OwnerType>::add(void* owner, CollisionShape* shape, Collider::ICollisionStrategy* strategy,
                                   glm::vec3* followPosition)
{
    id_t nextId = colliders.size();
    colliders.emplace_back(nextId, owner, shape, strategy, followPosition);
}