#include "Bullet.h"
#include "engine/App.h"
#include "game/Game.h"

Bullet::Bullet(glm::vec3 position, float rotationZ, glm::vec3 direction) : Entity3D(position, rotationZ)
{
    forward = direction;
    velocity = forward * speed;
}

void Bullet::update()
{
    position += velocity * App::deltaTime;

    // if (position.z <= 0 || position.z >= clippingY) Game::world.queueRemoveChild(this);
}
