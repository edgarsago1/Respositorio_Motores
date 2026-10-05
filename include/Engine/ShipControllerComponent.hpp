#pragma once

#include "Component.hpp"
#include "../Math/Vector2.hpp" 
#include <vector>
class ShipControllerComponent : public Component{
    protected:
        float speed{300.0f};
        float angular_speed{90.0f};
        Vector2 orientation{0.0f, 1.0f};
        int shoot_cooldown{10}; // Número de fotogramas mínimo que deben ocurrir entre cada nuevo disparo.
        int current_cooldown{10}; // Contador actual de fotogramas que han transcurrido
        std::vector<Vector2> trianglevertex{{-0.5f, 0}, {0.5f, 0}};

    public:
        bool follow_mouse{true};

        bool left_click_pressed{false};

        ShipControllerComponent() = default;

        explicit ShipControllerComponent(float spd, float angular_spd, int cooldown, bool mouse_follow = true) : speed(spd), angular_speed(angular_spd), shoot_cooldown(cooldown), follow_mouse(mouse_follow) {
            current_cooldown = shoot_cooldown;
        }

        Vector2 getOrientation();

        std::vector<Vector2> getTriangleVertex();

        void FixedUpdate(float fixed_dt) override;

};