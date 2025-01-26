#pragma once

#include "glm/vec3.hpp"
#include "engine/Id.h"
#include "engine/collision/CollisionShape.h"

template<typename T>
class Collider;

template<typename T>
class Collider
{
public:
    id_t id = 0;
    T* owner = nullptr;
    glm::vec3* followPosition = nullptr;
    CollisionShape& shape;

    Collider(T* owner, glm::vec3* followPosition, CollisionShape& shape) :
            owner(owner), followPosition(followPosition), shape(shape) {};

    template<typename U>
    Collider<U>* collide(Collider<U>& other);
    template<typename U>
    Collider<U>* physCollide(Collider<U>& other);
    template<typename U>
    bool collideGroup(std::vector<Collider<U>*>& colliderGroup);
    template<typename U>
    bool physCollideGroup(std::vector<Collider<U>*>& colliderGroup);
};

template<typename T>
template<typename U>
Collider<U>* Collider<T>::collide(Collider<U>& other)
{
    return nullptr;
}

template<typename T>
template<typename U>
Collider<U>* Collider<T>::physCollide(Collider<U>& other)
{
    return nullptr;
}

template<typename T>
template<typename U>
bool Collider<T>::collideGroup(std::vector<Collider<U>*>& colliderGroup)
{
    Collider<U>* lastCollision = nullptr;

    for (auto& collider : colliderGroup)
    {

    }

    return lastCollision;
}

template<typename T>
template<typename U>
bool Collider<T>::physCollideGroup(std::vector<Collider<U>*>& colliderGroup)
{
    Collider<U>* lastCollision = nullptr;

    for (auto& collider : colliderGroup)
    {

    }

    return lastCollision;
}

template <typename T>
class SoftCollider : public Collider<T>
{
    float push = 0;
    float spring = 1; // 1: constant push, >0: Push gets stronger as other collider approaches center

    SoftCollider(T* owner, glm::vec3* followPosition, CollisionShape& shape, float push, float spring) :
                Collider<T>(owner, followPosition, shape), push(push), spring(spring) {};

    // Special physics collide for soft collisions
    template<typename U>
    Collider<U>* physCollide(Collider<U>& other);
};

template<typename T>
template<typename U>
Collider<U>* SoftCollider<T>::physCollide(Collider<U>& other)
{
    return nullptr;
}
