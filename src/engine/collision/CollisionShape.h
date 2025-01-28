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


    struct HitData
    {
        glm::vec3 normal;
        float intersection;

        HitData(float intersection = 0, glm::vec3 normal = glm::vec3(0, 0, 0)) :
                intersection(intersection), normal(normal) {};
    };

    struct Hit
    {
        HitData data;
        bool confirmed;

        Hit(bool confirmed = false, HitData data = HitData()) : confirmed(confirmed), data(data) {};
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
