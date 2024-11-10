#include "Utils.h"
#include "glm/glm.hpp"

glm::vec2 Utils::vec2Rotated(glm::vec2 vec, float angle)
{
    return {vec.x * glm::cos(angle) - vec.y * glm::sin(angle),
            vec.x * glm::sin(angle) + vec.y * glm::cos(angle)};
}

float Utils::vec3Distance(const glm::vec3& a, const glm::vec3& b)
{
    return std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2);
}