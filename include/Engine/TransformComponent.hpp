#pragma once

#include "Component.hpp"
#include "../../include/Math/Vector2.hpp"

class TransformComponent : public Component
{
    public:
    Vector2 position{0.0f, 0.0f};
    Vector2 scale{1.0f, 1.0f};

    TransformComponent() = default;
    explicit TransformComponent(Vector2 pos) : position(pos) {}
    TransformComponent(Vector2 pos, Vector2 scl) : position(pos), scale(scl) {}

    void Translate(const Vector2 &offset);
    void Rotate(const float angular_speed, Vector2* orientation_vector);
};