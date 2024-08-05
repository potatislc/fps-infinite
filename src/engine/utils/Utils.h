#pragma once

#include <cstdio>

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
    namespace DefaultColors
    {
        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 255};
        SDL_Color inivsible = {0, 0, 0, 0};
    }
}

//
// Using so I don't want to write the namespace every time
//

using Utils::uint;
using namespace Utils::DefaultColors;