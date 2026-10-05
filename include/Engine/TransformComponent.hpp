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
    // Nueva función que permite transportar a un objeto a una posición nueva, en este caso, hacemos que su posición sea el extremo contrario de la pantalla que pasó
    void teleportObject(Vector2 max_bounds, Vector2 min_bounds);
};