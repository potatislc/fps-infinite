#pragma once

#include "glm/glm.hpp"
#include "engine/utils/Utils.h"

class CollisionShape;
class ShapeSphere;
class ShapeCircle;
class ShapeRect;

class CollisionShape
{
public:
    enum class Type
    {
        SPHERE,
        CIRCLE,
        RECT,
        SIZE
    };

    struct TouchingCells
    {
        uint32_t* array = nullptr;
        uint_t size = 0;
        uint_t width = 0;
    };

    struct Hit
    {
        float distSq;
        float distThreshold; // If distSq < distThreshold^2, then hit
        glm::vec3 normal = {0, 0, 0};

        Hit(float distSq = 0, float distThreshold = 0, glm::vec3 normal = glm::vec3(0, 0, 0)) :
                distSq(distSq), distThreshold(distThreshold), normal(normal) {};

        operator bool() const
        {
            return (distSq < distThreshold * distThreshold);
        }
    };

    Type type;
    glm::vec3* followPosition = nullptr;
    TouchingCells touchingCells;

    virtual Hit collideWith(CollisionShape& other) = 0;
    virtual Hit collideWithSphere(ShapeSphere& other) = 0;
    virtual Hit collideWithCircle(ShapeCircle& other) = 0;
    virtual Hit collideWithRect(ShapeRect& other) = 0;
    virtual void computeTouchingCells(int gridWidth /* Grid width (in cells)*/, float cellWidth) = 0;

protected:
    explicit CollisionShape(Type shapeType) : type(shapeType) {}

};

class ShapeSphere : public CollisionShape
{
public:
    float radius;

    ShapeSphere(float radius = 1.0f)
            : CollisionShape(Type::SPHERE), radius(radius) {};

    Hit collideWith(CollisionShape& other) override;
    Hit collideWithSphere(ShapeSphere& other) override;
};

class ShapeCircle : public CollisionShape
{
public:
    float radius;

    ShapeCircle(float cellWidth, float radius = 1.0f);

    Hit collideWith(CollisionShape& other) override;
    Hit collideWithRect(ShapeRect& other) override;
    Hit collideWithCircle(ShapeCircle& other) override;
    Hit collideWithSphere(ShapeSphere& other) override;
    void computeTouchingCells(int gridWidth /* Grid width (in cells)*/, float cellWidth) override;
};

class ShapeRect : public CollisionShape
{
public:
    glm::vec2 halfSize; // Half extents of the rectangle

    ShapeRect(glm::vec2 size)
            : CollisionShape(Type::RECT), halfSize(size * 0.5f) {}

    Hit collideWith(CollisionShape& other) override;
    Hit collideWithCircle(ShapeCircle& other) override;
    Hit collideWithSphere(ShapeSphere& other) override;
    Hit collideWithRect(ShapeRect& other) override;
};
