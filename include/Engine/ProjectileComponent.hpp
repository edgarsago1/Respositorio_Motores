#include "Component.hpp"
#include "../Math/Vector2.hpp"

class ProjectileComponent : public Component{
    public:
    Vector2 velocity{220.0f, 180.0f};
    Vector2 projectile_size{5.0f, 5.0f};
    Vector2 direction{1.0f, 0.0f};
    float max_travelDistance{200.0f};
    float traveled_distance{0.0f};
    ProjectileComponent(Vector2 spd, Vector2 size, Vector2 new_direction, float max) : velocity(spd), projectile_size(size), direction(new_direction), max_travelDistance(max) {}
    void FixedUpdate(float fixed_dt) override;
};