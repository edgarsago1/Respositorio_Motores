#pragma once
#include <cmath>
#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

class PatrolComponent : public Component
{
    public:
    float speed{100.0f};
    float distance{150.0f};
    float origin_x{0.0f};
    float timer{0.0f};

    PatrolComponent(float spd, float dist) : speed(spd), distance(dist) {}

    void Init() override
    {
        if (auto *t = owner->GetComponent<TransformComponent>())
        {
            origin_x = t->position.x;
        }
    }

    void Update(float dt) override
    {
        if (auto *t = owner->GetComponent<TransformComponent>())
        {
            timer += dt * (speed / 50.0f);
            t->position.x = origin_x + std::sin(timer) * distance;
        }
    }
};