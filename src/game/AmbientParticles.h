#pragma once

#include <cstdint>
#include <array>
#include "glm/vec3.hpp"
#include "engine/Camera3D.h"

class AmbientParticles
{
public:
    static const uint8_t maxParticles = 255;
    const float radius;

    AmbientParticles(uint8_t count, float radius);
    static void draw(SDL_Renderer* renderer, SDL_Rect& viewport, Camera3D& camera, float time);
};