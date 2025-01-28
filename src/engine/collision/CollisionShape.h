#pragma once

#include <glm/glm.hpp>

class CollisionShape;
class ShapeCircle;
class ShapeCylinder;

class CollisionShape
{
public:
    enum class Type
    {
        POINT,
        CIRCLE,
        SPHERE,
        CYLINDER,
        SIZE
    };

    Type type;
    glm::vec3* followPosition = nullptr;

    struct Hit
    {
        float distSq;
        float distThreshold; // If distSq < distThreshold^2, then hit
        glm::vec3 normal;

        Hit(float distSq = 0, float distThreshold = 0, glm::vec3 normal = glm::vec3(0, 0, 0)) :
                distSq(distSq), distThreshold(distThreshold), normal(normal) {};

        // Nodiscard means you can't ignore return value when calling function
        [[nodiscard]] bool isConfirmed() const
        {
            return (distSq < distThreshold * distThreshold);
        }
    };

    virtual Hit collideWith(CollisionShape& other) = 0;
    virtual Hit collideWithCircle(ShapeCircle& other) = 0;
    virtual Hit collideWithCylinder(ShapeCylinder& other) = 0;

protected:
    explicit CollisionShape(Type shapeType) : type(shapeType) {}

};

class ShapeCircle : public CollisionShape
{
public:
    float radius;

    ShapeCircle(float radius = 1.0f)
            : CollisionShape(Type::CIRCLE), radius(radius) {};

    Hit collideWith(CollisionShape& other) override
    {
        return other.collideWithCircle(*this);
    }

    Hit collideWithCircle(ShapeCircle& other) override
    {
        glm::vec2 deltaXYSq = glm::vec2(other.followPosition->x - followPosition->x,
                                        other.followPosition->y - followPosition->y);
        deltaXYSq *= deltaXYSq;
        float distSq = deltaXYSq.x + deltaXYSq.y;
        float thresholdSq = radius * radius + other.radius * other.radius;

        if (distSq < thresholdSq)
        {
            return {distSq, radius + other.radius, glm::normalize(glm::vec3(deltaXYSq.x, deltaXYSq.y, 0))};
        }

        return {};
    }
};

class ShapeCylinder : public CollisionShape
{
public:
    float top;
    float bottom;
    float radius;

    ShapeCylinder(float top = 1.0f, float bottom = -1.0f, float radius = 1.0f)
            : CollisionShape(Type::CYLINDER), top(top), bottom(bottom), radius(radius) {};

    Hit collideWith(CollisionShape& other) override
    {
        return other.collideWithCylinder(*this);
    }
};
