#include "../../include/Engine/TransformComponent.hpp"

void TransformComponent::Translate(const Vector2 &offset)
    {
        position = position + offset;
    }