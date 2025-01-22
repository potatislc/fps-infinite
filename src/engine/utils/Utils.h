#pragma once

#include <cstdio>
#include <SDL.h>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Utils
{
    typedef unsigned int uint;

    //
    // Math
    //
    template <typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    template <typename T>
    T fmod(T a, T b)
    {
        return a - b * std::floor(a / b);
    }

    glm::vec2 vec2Rotate(glm::vec2 vec, float angle);
    glm::vec2 vec2DeltaWrapped(glm::vec2 a, glm::vec2 b, const glm::vec2& bounds);

    //
    // Vector
    //
    class Vector2
    {
    public:
        float x;
        float y;

        Vector2(float x, float y) : x(x), y(y) {};
    };

    class Vector2I
    {
    public:
        int x;
        int y;

        Vector2I(int x, int y) : x(x), y(y) {};
    };

    class Vector2UI
    {
    public:
        uint x;
        uint y;

        Vector2UI(uint x, uint y) : x(x), y(y) {};
    };

    //
    // Rand
    //
    size_t uRand(size_t val);
    size_t uRandRange(uint min, uint max);
    int randRange(int min, int max);

    //
    // Default Colors
    //
    namespace Colors
    {
        extern const SDL_Color white;
        extern const SDL_Color black;
        extern const SDL_Color invisible;

        extern const SDL_Color red;
        extern const SDL_Color green;
        extern const SDL_Color blue;
        extern const SDL_Color yellow;
    }
}

using Utils::uint;