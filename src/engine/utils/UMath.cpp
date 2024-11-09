#include "Utils.h"

glm::vec2 Utils::vec2Rotated(glm::vec2 vec, float angle)
{
    return {vec.x * std::cos(angle) - vec.y * std::sin(angle),
                     vec.x * std::sin(angle) + vec.y * std::cos(angle)};
}