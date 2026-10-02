#pragma once

#include "Component.hpp"

class PlayerControllerComponent : public Component
{
    public:
        float speed{300.0f};
        bool follow_mouse{true};

        PlayerControllerComponent() = default;
        explicit PlayerControllerComponent(float spd, bool mouse_follow = true) : speed(spd), follow_mouse(mouse_follow) {}

        void FixedUpdate(float fixed_dt) override;
};