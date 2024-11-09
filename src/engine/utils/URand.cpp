#include <cstdlib>
#include "Utils.h"

size_t Utils::uRand(size_t val)
{
    return std::rand() % (val + 1);
}

#define RAND_RANGE(min, max) min + (std::rand() % (max - min + 1))

size_t Utils::uRandRange(uint min, uint max)
{
    return RAND_RANGE(min, max);
}

int Utils::randRange(int min, int max)
{
    return RAND_RANGE(min, max);
}
