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

    float distSq = delta.x * delta.x + delta.y * delta.y; // glm::dot(delta, delta); It's the same
    float thresholdSq = (radius + other.radius) * (radius + other.radius);

    if (distSq < thresholdSq)
    {
        float invLen = glm::inversesqrt(distSq); // This was not me
        return {distSq, radius + other.radius, glm::vec3(delta * invLen, 0)};
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

void ShapeCircle::computeTouchingCells(const int gridWidth, const float cellWidth)
{
    glm::vec2 pos = *followPosition;
    glm::vec2 cellPos = ((pos - glm::vec2(radius, radius)) / cellWidth);
    int baseX = static_cast<int>(cellPos.x);
    int baseY = static_cast<int>(cellPos.y);

    for (int i = 0; i < touchingCells.size; i++)
    {
        int offsetX = i % touchingCells.width;
        int offsetY = i / touchingCells.width;
        int cellId = ((baseY + offsetY + gridWidth) % gridWidth) * gridWidth
                     + ((baseX + offsetX + gridWidth) % gridWidth);
        touchingCells.array[i] = cellId;
    }
}

ShapeCircle::ShapeCircle(const float cellWidth, float radius) : CollisionShape(Type::CIRCLE), radius(radius)
{
    int cellsInDiameter = static_cast<int>(2 * radius / cellWidth) + 2;
    uint_t touchingCellsMaxSize = cellsInDiameter * cellsInDiameter;
    touchingCells = {new uint32_t[touchingCellsMaxSize], touchingCellsMaxSize, static_cast<uint_t>(cellsInDiameter)};
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
