#include "Eye.h"
#include "engine/App.h"
#include "game/Game.h"
#include "engine/ResourceLoader.h"
#include "game_setup/ColliderGroups.h"

float Eye::globalHoverOffset = 0;

Eye::Eye(glm::vec3 position, float rotationY, int hp, std::shared_ptr<Player>& player)
    : ACharacter(position, rotationY, hp), player(player)
{
    globalHoverOffset += .1;
    hoverOffset = globalHoverOffset;
}

void Eye::start()
{
    colliderId = ColliderGroups::eyes.add(this, new ShapeCircle(), new Collider::SolidCollision2D(), &position);
}

void Eye::update()
{
    glm::vec2 targetDirXY = glm::normalize(Utils::vec2DeltaWrapped(position, player->position, Game::cellSize));
    float targetDirZ = glm::sin((float)App::timeSinceInit + hoverOffset) * hoverMag + hoverHeight - position.z;

    velocity += glm::vec3(targetDirXY.x, targetDirXY.y, targetDirZ) * accel * App::deltaTime;

    if (glm::length(velocity) > maxSpeed)
    {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    glm::vec3 lastPos = position;
    position += velocity * App::deltaTime;
    forward = glm::normalize(position - lastPos);

    // Use ColliderGroup::collideAll() inside game loop instead.
    // ColliderGroups::eyes.colliders[colliderId].collideGroupNaive(ColliderGroups::eyes);
}

void Eye::draw(SDL_Renderer* renderer)
{
    Game::camera3D.drawTexture3DEx(renderer, ResourceLoader::loadedTextures.swarm, position, forward,
                                   App::renderer.viewport);
}
