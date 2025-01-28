#pragma once

#include <memory>
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

    Collider(void* owner, CollisionShape* shape, ICollisionStrategy* strategy, glm::vec3* followPosition) :
            owner(owner), shape(shape), strategy(strategy)
    {
        shape->followPosition = followPosition;
    };

    template <typename T>
    struct Hit
    {
        Collider* collider;
        T* owner;
        CollisionShape::HitData data;

        Hit(Collider* collider = nullptr, T* owner = nullptr,
            CollisionShape::HitData data = CollisionShape::HitData()) :
                collider(collider), owner(owner), data(data) {};

        bool isConfirmed()
        {
            return collider;
        };
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

    for (Collider* other : colliderGroup.colliders)
    {
        CollisionShape::Hit hit = strategy->collide(*shape, *other);
        if (hit.confirmed)
        {
            lastHit = Collider::Hit<T>(other, static_cast<T*>(other->owner), hit.data);
        }
    }

    return lastHit;
}

template<typename T>
Collider::Hit<T> Collider::collideGroupNaive(ColliderGroup<T>& colliderGroup)
{

}
