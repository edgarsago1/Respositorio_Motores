#pragma once


#include "Component.hpp"
#include "../Math/Vector2.hpp"

class BallComponent : public Component{
    public:
    Vector2 velocity{220.0f, 180.0f};
    Vector2 ball_size{24.0f, 24.0f};

    void FixedUpdate(float fixed_dt) override;
    void OnCollision(GameObject *other) override;
};