#pragma once
#include "Component.hpp"
#include "../Math/Vector2.hpp"

class ProjectileComponent : public Component{
    private:
        float speed{300.0f};
        Vector2 projectile_size{5.0f, 5.0f};
        Vector2 direction{1.0f, 0.0f};
        float max_travelDistance{200.0f};
        float traveled_distance{0.0f};
    public:
        ProjectileComponent(float spd, Vector2 size, Vector2 new_direction, float max) : speed(spd), projectile_size(size), direction(new_direction), max_travelDistance(max) {}
        
        // Le damos un tiempo de vida util al proyectil antes de destruirlo 
        void FixedUpdate(float fixed_dt) override;

        // Obligamos a que el proyectil se destruya al colisionar con otro objeto
        void OnCollision(GameObject *other) override;
};