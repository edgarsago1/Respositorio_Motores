#define _USE_MATH_DEFINES
#include <cmath>
#include "../../include/Engine/TransformComponent.hpp"
double pi = M_PI;

void TransformComponent::Translate(const Vector2 &offset){
        position = position + offset;
    }

void TransformComponent::Rotate(const float angular_speed, Vector2* orientation_vector){
    float rad = angular_speed * pi / 180.0f;
    float x = orientation_vector->x;
    float y = orientation_vector->y;
    orientation_vector->x = x * std::cos(rad) - y * std::sin(rad);
    orientation_vector->y = x * std::sin(rad) + y * std::cos(rad);
}

void TransformComponent::teleportObject(Vector2 max_bounds, Vector2 min_bounds){
    if (position.x < min_bounds.x) {
        position.x = max_bounds.x;
    } else if (position.x > max_bounds.x) {
        position.x = min_bounds.x;
    }
    if (position.y < min_bounds.y) {
        position.y = max_bounds.y;
    } else if (position.y > max_bounds.y) {
        position.y = min_bounds.y;
    }
}