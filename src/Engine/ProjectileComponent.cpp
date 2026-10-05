#include "../../include/Engine/ProjectileComponent.hpp"

#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp"

void ProjectileComponent::FixedUpdate(float fixed_dt){
    if(!owner) return;
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if(!transform) return;
    direction = direction.normalized();
    Vector2 movement = {direction.x * velocity.x * fixed_dt, direction.y * velocity.y * fixed_dt};
    transform->Translate(movement);
    traveled_distance = traveled_distance + movement.length();
    Vector2 max_bounds{960.0f, 540.0f};
    transform->teleportObject(max_bounds, {0.0f, 0.0f});
    if(traveled_distance >= max_travelDistance)
        owner->Destroy();
}