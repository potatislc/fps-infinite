#include "engine/collision/CollisionShape.h"

CollisionShape::Hit ShapeSphere::collideWith(CollisionShape& other)
{
    return other.collideWithSphere(*this);
}

CollisionShape::Hit ShapeSphere::collideWithSphere(ShapeSphere& other)
{
    glm::vec3 delta = *other.followPosition - *followPosition;

    float distSq = glm::dot(delta, delta);
    float thresholdSq = (radius + other.radius) * (radius + other.radius);

    if (distSq < thresholdSq)
    {
        return {distSq, radius + other.radius, glm::normalize(delta)};
        // Returns a hit object with (distanceSquared, minimum distance for hit and the collision normal)
    }

    return {};
}

CollisionShape::Hit ShapeCircle::collideWith(CollisionShape& other)
{
    return other.collideWithCircle(*this);
}

CollisionShape::Hit ShapeCircle::collideWithRect(ShapeRect& other)
{
    return other.collideWithCircle(*this);
}

CollisionShape::Hit ShapeCircle::collideWithCircle(ShapeCircle& other)
{
    glm::vec2 delta = *other.followPosition - *followPosition;

    float distSq = glm::dot(delta, delta);
    float thresholdSq = (radius + other.radius) * (radius + other.radius);

    if (distSq < thresholdSq)
    {
        return {distSq, radius + other.radius, glm::normalize(glm::vec3(delta.x, delta.y, 0))};
        // Returns a hit object with (distanceSquared, minimum distance for hit and the collision normal)
    }

    return {};
}

CollisionShape::Hit ShapeCircle::collideWithSphere(ShapeSphere& other)
{
    glm::vec2 delta = *other.followPosition - *followPosition;

    float distSq = glm::dot(delta, delta);
    float thresholdSq = (radius + other.radius) * (radius + other.radius);

    if (distSq < thresholdSq)
    {
        return {distSq, radius + other.radius, glm::normalize(glm::vec3(delta.x, delta.y, 0))};
        // Returns a hit object with (distanceSquared, minimum distance for hit and the collision normal)
    }

    return {};
}

std::vector<uint32_t> ShapeCircle::touchingCells(const int gridWidth, const float cellWidth)
{
    glm::vec2 pos = *followPosition;
    std::vector<uint32_t> touchingCells;

    int minX = static_cast<int>(std::floor((pos.x - radius) / cellWidth));
    int maxX = static_cast<int>(std::floor((pos.x + radius) / cellWidth));
    int minY = static_cast<int>(std::floor((pos.y - radius) / cellWidth));
    int maxY = static_cast<int>(std::floor((pos.y + radius) / cellWidth));

    for (int y = minY; y <= maxY; y++)
    {
        int wrappedY = ((y % gridWidth) + gridWidth) % gridWidth;
        for (int x = minX; x <= maxX; x++)
        {

            glm::vec2 closest = {std::max(x * cellWidth, std::min(pos.x, (x + 1) * cellWidth)),
                                 std::max(y * cellWidth, std::min(pos.y, (y + 1) * cellWidth))};
            glm::vec2 dist = pos - closest;
            float distSq = dist.x * dist.x + dist.y * dist.y;
            if ((distSq) <= (radius * radius))
            {
                int wrappedX = ((x % gridWidth) + gridWidth) % gridWidth;
                uint32_t wrappedIndex = wrappedY * gridWidth + wrappedX;
                touchingCells.push_back(wrappedIndex);
            }
        }
    }

    return touchingCells;
}

CollisionShape::Hit ShapeRect::collideWith(CollisionShape& other)
{
    return other.collideWithRect(*this);
}

CollisionShape::Hit ShapeRect::collideWithCircle(ShapeCircle& other)
{
    glm::vec2 circlePos = glm::vec2(*other.followPosition);
    glm::vec2 rectPos = glm::vec2(*followPosition);

    glm::vec2 closestPoint = glm::clamp(circlePos, rectPos - halfSize, rectPos + halfSize);
    glm::vec2 delta = circlePos - closestPoint;
    float distSq = glm::dot(delta, delta);

    if (distSq < other.radius * other.radius)
    {
        return {distSq, other.radius, glm::normalize(glm::vec3(delta, 0))};
    }
    return {};
}

CollisionShape::Hit ShapeRect::collideWithSphere(ShapeSphere& other)
{
    return other.collideWithRect(*this);
}

CollisionShape::Hit ShapeRect::collideWithRect(ShapeRect& other)
{
    auto posA = glm::vec2(*followPosition);
    auto posB = glm::vec2(*other.followPosition);

    glm::vec2 delta = posB - posA;
    glm::vec2 overlap = halfSize + other.halfSize - glm::abs(delta);

    if (overlap.x > 0 && overlap.y > 0)
    {
        glm::vec3 normal = (overlap.x < overlap.y) ? glm::vec3(glm::sign(delta.x), 0, 0)
                                                   : glm::vec3(0, glm::sign(delta.y), 0);
        return {0, 0, normal};
    }
    return {};
}