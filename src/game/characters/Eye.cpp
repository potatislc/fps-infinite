#include "Eye.h"
#include "engine/App.h"
#include "game/Game.h"
#include "engine/ResourceLoader.h"

Eye::Eye(glm::vec3 position, float rotationY, int hp, std::shared_ptr<Player>& player)
    : ACharacter(position, rotationY, hp), player(player)
{

}

void Eye::start()
{

}

void Eye::update()
{
    glm::vec3 targetDir = glm::normalize(player->position - position);
    targetDir.z = (glm::sin((float)App::timeSinceInit) + hoverHeight) * hoverMag - position.z;

    velocity += targetDir * accel * App::deltaTime;

    if (glm::length(velocity) > maxSpeed)
    {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    position += velocity * App::deltaTime;
}

void Eye::draw(SDL_Renderer* renderer)
{
    Game::camera3D.drawTexture3DEx(renderer, ResourceLoader::loadedTextures.swarm, position, velocity,
                                   App::renderer.viewport);
}
