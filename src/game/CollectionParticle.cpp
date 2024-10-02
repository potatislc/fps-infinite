
#include "game/CollectionParticle.h"
#include "engine/Application.h"

void CollectionParticle::start()
{
    float blastAngle = glm::radians((float)Utils::uRand(360));
    blastVelocity = (glm::vec2){cos(blastAngle) * blastSpeed, sin(blastAngle) * blastSpeed};
}

void CollectionParticle::update()
{
    blastVelocity -= glm::normalize(blastVelocity) * blastDecel * (float)Application::deltaTime;
    position += blastVelocity * (float)Application::deltaTime;

    glm::vec2 pullDir = glm::normalize(targetPosition - position);
    pullVelocity += pullDir * pullSpeed * (float)Application::deltaTime;
    position += pullVelocity * (float)Application::deltaTime;
}

void CollectionParticle::draw(SDL_Renderer *renderTarget)
{
    SDL_Rect src = {(int)position.x, (int)position.y, 8, 8};
    SDL_SetRenderDrawColor(renderTarget, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderTarget, &src);
}
