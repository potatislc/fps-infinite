#pragma once

#include <cstdio>
#include <SDL.h>

namespace Utils
{
    typedef unsigned int uint;

    //
    // Vector
    //

    struct Vector2
    {
        float x;
        float y;
    };

    struct Vector2I
    {
        int x;
        int y;
    };

    struct UVector2I
    {
        uint x;
        uint y;
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