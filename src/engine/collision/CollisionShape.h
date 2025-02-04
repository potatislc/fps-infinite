#pragma once

#include <glm/glm.hpp>

class CollisionShape;
class ShapeSphere;
class ShapeCircle;
class ShapeCylinder;

class CollisionShape
{
public:
    enum class Type
    {
        POINT,
        SPHERE,
        CIRCLE,
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

        operator bool() const
        {
            return (distSq < distThreshold * distThreshold);
        }
    };

    virtual Hit collideWith(CollisionShape& other) = 0;
    virtual Hit collideWithSphere(ShapeSphere& other) = 0;
    virtual Hit collideWithCircle(ShapeCircle& other) = 0;
    // virtual Hit collideWithCylinder(ShapeCylinder& other) = 0;

protected:
    explicit CollisionShape(Type shapeType) : type(shapeType) {}

};

class ShapeSphere : public CollisionShape
{
public:
    float radius;

    ShapeSphere(float radius = 1.0f)
            : CollisionShape(Type::SPHERE), radius(radius) {};

    Hit collideWith(CollisionShape& other) override
    {
        return other.collideWithSphere(*this);
    }

    Hit collideWithSphere(ShapeSphere& other) override
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

    Hit collideWithSphere(ShapeSphere& other) override
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

    Hit collideWithCircle(ShapeCircle& other) override
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
};

/*class ShapeCylinder : public CollisionShape
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
};*/
