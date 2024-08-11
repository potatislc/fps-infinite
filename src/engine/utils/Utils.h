#pragma once

#include <cstdio>
#include <SDL.h>

namespace Utils
{
    typedef unsigned int uint;

    //
    // Math
    //

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