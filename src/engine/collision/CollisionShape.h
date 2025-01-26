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
    };

    Type type;

    virtual float collideWith(CollisionShape& other) = 0;
    virtual float collideWithCircle(ShapeCircle& other) = 0;
    virtual float collideWithCylinder(ShapeCylinder& other) = 0;

protected:
    explicit CollisionShape(Type shapeType) : type(shapeType) {}

};

class ShapeCircle : public CollisionShape
{
    float radius;

    ShapeCircle(float radius = 1.0f)
            : CollisionShape(Type::CIRCLE), radius(radius) {}
};

class ShapeCylinder : public CollisionShape
{
    float top;
    float bottom;
    float radius;

    ShapeCylinder(float top = 1.0f, float bottom = -1.0f, float radius = 1.0f)
            : CollisionShape(Type::CYLINDER), top(top), bottom(bottom), radius(radius) {}
};
