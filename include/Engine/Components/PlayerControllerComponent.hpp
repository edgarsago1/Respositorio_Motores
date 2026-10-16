#pragma once

#include <SDL3/SDL.h>

#include "../Component.hpp"
#include "../GameObject.hpp"
#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"
#include "../../Math/Vector2.hpp"
class PlayerControllerComponent : public Component
{
    public:
        float speed{300.0f};
        PlayerControllerComponent() = default;
        explicit PlayerControllerComponent(float spd) : speed(spd) {}

        void FixedUpdate(float fixed_dt) override;
};