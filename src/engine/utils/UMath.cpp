#include "Utils.h"
#include "glm/glm.hpp"

glm::vec2 Utils::vec2Rotated(glm::vec2 vec, float angle)
{
    return {vec.x * glm::cos(angle) - vec.y * glm::sin(angle),
            vec.x * glm::sin(angle) + vec.y * glm::cos(angle)};
}