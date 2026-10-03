#include "../../include/Engine/TransformComponent.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

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