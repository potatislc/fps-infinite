#pragma once

#include <glm/glm.hpp>

struct CollisionShape
{
    enum class Type
    {
        CIRCLE,
        CYLINDER,
        RECT,
        BOX
    };

protected:
    explicit CollisionShape(Type shapeType) : type(shapeType) {}

public:
    Type type;
};

struct ShapeCircle : public CollisionShape
{
    float radius;

    ShapeCircle(float radius = 1.0f)
            : CollisionShape(Type::CIRCLE), radius(radius) {}
};

struct ShapeCylinder : public CollisionShape {
    float top;
    float bottom;
    float radius;

    ShapeCylinder(float top = 1.0f, float bottom = -1.0f, float radius = 1.0f)
            : CollisionShape(Type::CYLINDER), top(top), bottom(bottom), radius(radius) {}
};

struct ShapeRect : public CollisionShape
{
    glm::vec2 a;
    glm::vec2 b;

    ShapeRect(glm::vec2 a = glm::vec2(0, 0), glm::vec2 b = glm::vec2(1, 1))
            : CollisionShape(Type::RECT), a(a), b(b) {}
};

struct ShapeBox : public CollisionShape
{
    glm::vec3 a;
    glm::vec3 b;

    ShapeBox(glm::vec3 a = glm::vec3(0, 0, 1), glm::vec3 b = glm::vec3(1, 1, -1))
            : CollisionShape(Type::BOX), a(a), b(b) {}
};
