#pragma once

#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"

template<typename T>
class Collider
{
public:
    id_t id = 0;
    T& owner;
    glm::vec3& followPosition;
    CollisionShape shape;

    Collider(T& owner, glm::vec3& followPosition, CollisionShape shape) :
            owner(owner), followPosition(followPosition), shape(shape) {};

    template<typename U>
    bool isColliding(std::vector<Collider<U>*>& colliderGroup);
    template<typename U>
    bool physCollide(std::vector<Collider<U>*>& colliderGroup);
    template<typename U>
    bool isCollidingGroup(std::vector<Collider<U>*>& colliderGroup);
    template<typename U>
    bool physCollideGroup(std::vector<Collider<U>*>& colliderGroup);
};

template<typename T>
template<typename U>
bool Collider<T>::isColliding(std::vector<Collider<U>*>& colliderGroup)
{
    return false;
}

template<typename T>
template<typename U>
bool Collider<T>::physCollide(std::vector<Collider<U>*>& colliderGroup)
{
    return false;
}

template<typename T>
template<typename U>
bool Collider<T>::isCollidingGroup(std::vector<Collider<U>*>& colliderGroup)
{
    bool collision = false;

    for (auto& collider : colliderGroup)
    {

    }

    return collision;
}

template<typename T>
template<typename U>
bool Collider<T>::physCollideGroup(std::vector<Collider<U>*>& colliderGroup)
{
    bool collision = false;

    for (auto& collider : colliderGroup)
    {

    }

    return collision;
}

template <typename T>
class SoftCollider : public Collider<T>
{
    float push = 0;
    float spring = 1; // 1: constant push, >0: Push gets stronger as other collider approaches center

    SoftCollider(T& owner, glm::vec3& followPosition, CollisionShape shape, float push, float spring) :
                Collider<T>(owner, followPosition, shape), push(push), spring(spring) {};
};

template <typename T>
class SoftCircleCollider : public SoftCollider<T>
{
    float radius = 1;
    SoftCircleCollider(T& owner, glm::vec3& followPosition, CollisionShape shape, float push, float spring,
                       float radius) : SoftCollider<T>(owner, followPosition, shape, push, spring), radius(radius) {};
};