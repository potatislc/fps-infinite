#pragma once

#include "engine/utils/Utils.h"

class CollectionParticle
{
    Utils::Vector2 postition;
    const Utils::Vector2 targetPostion;
    CollectionParticle(Utils::Vector2 position, Utils::Vector2 targetPosition) :
        postition(position), targetPostion(targetPosition) {};

};