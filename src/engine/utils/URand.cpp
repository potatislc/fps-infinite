#include <cstdlib>
#include "Utils.h"

size_t Utils::randi(size_t val)
{
    return rand() % (val + 1);
}

int Utils::randiRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}