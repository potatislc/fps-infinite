#pragma once

#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"

class Collider;

template <typename Owner>
class ColliderGroup
{
    std::vector<Collider*> colliders;
};

class Collider
{
public:

    class ICollisionStrategy
    {
    public:
        virtual Collider* collide(CollisionShape& myShape, Collider* other) = 0;
    };

    class TriggerCollision : public ICollisionStrategy
    {
    public:
        Collider* collide(CollisionShape& myShape, Collider* other) override
        {
            return (myShape.collideWith(other->shape) != NO_COLLISION) ? other : nullptr;
        };
    };

    class SolidCollision : public ICollisionStrategy
    {
    public:
        Collider* collide(CollisionShape& myShape, Collider* other) override
        {
            return nullptr;
        };
    };

    class SoftCollision : public ICollisionStrategy
    {
    public:
        float push = 0;
        float spring = 0;
        Collider* collide(CollisionShape& myShape, Collider* other) override
        {
            return nullptr;
        };
    };

    id_t id = 0;
    void* owner = nullptr;
    CollisionShape& shape;
    ICollisionStrategy& strategy;

    Collider(void* owner, CollisionShape& shape, ICollisionStrategy& strategy, glm::vec3* followPosition) :
            owner(owner), shape(shape), strategy(strategy)
    {
        shape.followPosition = followPosition;
    };

    template <typename T>
    struct Hit
    {
        Collider* collider;
        T* owner;
        // glm::vec3 normal;

        Hit(Collider* collider, T* owner) : collider(collider), owner(owner) {};
    };

    template <typename T>
    Hit<T> collideGroup(ColliderGroup<T>& colliderGroup);
};

template <typename T>
Collider::Hit<T> Collider::collideGroup(ColliderGroup<T>& colliderGroup)
{
    Collider* lastCollision = nullptr;

    for (auto* other : colliderGroup.colliders)
    {
        Collider* collision = strategy.collide(other);
        if (collision) lastCollision = collision;
    }

    if (!lastCollision)
    {
        return Collider::Hit(nullptr, static_cast<T*>(nullptr));
    }
    else
    {
        return Collider::Hit(lastCollision, static_cast<T*>(lastCollision->owner));
    }
}
