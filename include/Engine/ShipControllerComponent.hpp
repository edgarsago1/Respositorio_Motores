#pragma once

#include "Component.hpp"
#include "../Math/Vector2.hpp" 
#include <vector>
class ShipControllerComponent : public Component{
    protected:
        float speed{300.0f};
        float angular_speed{90.0f};
        Vector2 orientation{0.0f, 1.0f};
        std::vector<Vector2> trianglevertex{{-0.5f, 0}, {0.5f, 0}};

    public:
        bool follow_mouse{true};

        bool left_click_pressed{false};

        ShipControllerComponent() = default;

        explicit ShipControllerComponent(float spd, float angular_spd,bool mouse_follow = true) : speed(spd), angular_speed(angular_spd), follow_mouse(mouse_follow) {}

        Vector2 getOrientation();

        std::vector<Vector2> getTriangleVertex();

        void FixedUpdate(float fixed_dt) override;

};