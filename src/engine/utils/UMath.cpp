#include "Utils.h"
#include "glm/glm.hpp"

glm::vec2 Utils::vec2Rotate(glm::vec2 vec, float angle)
{
    return {vec.x * glm::cos(angle) - vec.y * glm::sin(angle),
            vec.x * glm::sin(angle) + vec.y * glm::cos(angle)};
}

glm::vec2 Utils::vec2DeltaWrapped(glm::vec2 a, glm::vec2 b, const glm::vec2& bounds)
{
    glm::vec2 delta = b - a;
    glm::vec2 wrappedDelta = {
            delta.x - bounds.x * glm::round(delta.x / bounds.x),
            delta.y - bounds.y * glm::round(delta.y / bounds.y)
    };
    return wrappedDelta;
}
