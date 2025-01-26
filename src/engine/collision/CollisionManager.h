#pragma once

#include <array>
#include <vector>
#include "Collider.h"
#include "game/characters/Player.h"

class CollisionManager
{
    template <typename T>
    void addCollider(std::vector<Collider<T>*>& colliderGroup, Collider<T>* collider);
};

template<typename T>
void CollisionManager::addCollider(std::vector<Collider<T>*>& colliderGroup, Collider<T>* collider)
{
    collider->id = (id_t)colliderGroup.size();
    colliderGroup.emplace_back(collider);
}
