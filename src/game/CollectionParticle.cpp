#include "game/CollectionParticle.h"
#include "engine/Application.h"

void CollectionParticle::start()
{
    float blastAngle = ((float)Utils::uRand(360) / 360) * (float)M_2_PI;
    blastVelocity = (Utils::Vector2){cos(blastAngle) * blastSpeed, sin(blastAngle) * blastSpeed};
}

void CollectionParticle::update()
{
    position = (Utils::Vector2){
        position.x + blastVelocity.x * (float)Application::deltaTime,
        position.y + blastVelocity.y * (float)Application::deltaTime
    };

    position = (Utils::Vector2){
            position.x + pullVelocity.x * (float)Application::deltaTime,
            position.y + pullVelocity.y * (float)Application::deltaTime
    };
}

void CollectionParticle::draw(SDL_Renderer *renderTarget)
{
    SDL_Rect src = {(int)position.x, (int)position.y, 8, 8};
    SDL_RenderDrawRect(renderTarget, &src);
}
