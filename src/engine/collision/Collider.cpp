#include "Collider.h"

bool Collider::collideWith(Collider& other)
{
    CollisionShape::Hit hit = strategy->collide(*shape, other);

    if (hit)
    {
        // std::cout << "Hit!" << std::endl;
        hitRes = Collider::Hit((Collider*)&other, other.owner, hit);
    }

    return static_cast<bool>(hit);
}