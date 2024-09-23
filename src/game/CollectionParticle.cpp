#include "game/CollectionParticle.h"

void CollectionParticle::start()
{
    blastAngle = ((float)Utils::uRand(360) / 360) * (float)M_2_PI;
    // blastVelocity = (Utils::Vector2){}
}

void CollectionParticle::update()
{

}

void CollectionParticle::draw(SDL_Renderer *renderTarget)
{

}
