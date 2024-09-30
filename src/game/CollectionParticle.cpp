
#include "game/CollectionParticle.h"
#include "engine/Application.h"

void CollectionParticle::start()
{
    float blastAngle = ((float)Utils::uRand(360) / 360) * (float)M_2_PI;
    blastVelocity = (glm::vec2){cos(blastAngle) * blastSpeed, sin(blastAngle) * blastSpeed};
}

void CollectionParticle::update()
{
    position += blastVelocity * (float)Application::deltaTime;
    position += pullVelocity * (float)Application::deltaTime;
}

void CollectionParticle::draw(SDL_Renderer *renderTarget)
{
    SDL_Rect src = {(int)position.x, (int)position.y, 8, 8};
    SDL_RenderDrawRect(renderTarget, &src);
}
