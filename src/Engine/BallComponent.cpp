#include "../../include/Engine/BallComponent.hpp"

#include <cmath>
#include <vector>
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Physics/ColliderComponent.hpp"

void BallComponent::FixedUpdate(float fixed_dt){
        if (!owner) return;
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
        if (!transform) return;
        transform->Translate(velocity * fixed_dt);
        ColliderComponent* collider = owner->GetComponent<ColliderComponent>();
        if (collider) 
            ball_size = collider->size * transform->scale.x;
        if(transform->position.x <= 0.0f){
            transform->position.x = 0;
            velocity.x = std::abs(velocity.x);
        }
        if(transform->position.x + ball_size.x >= 960.0f)
            velocity.x = -std::abs(velocity.x);
        if(transform->position.y <= 0.0f){
            transform->position.y = 0;
            velocity.y = std::abs(velocity.y);
        }
        if(transform->position.y + ball_size.y >= 540.0f)
            velocity.y = -std::abs(velocity.y);
    }

    void BallComponent::OnCollision(GameObject *other){
        if (!owner || !other) return;
        TransformComponent *transform_us = owner->GetComponent<TransformComponent>();
        TransformComponent *transform_other = other->GetComponent<TransformComponent>();
        if (!transform_us || !transform_other) return;
        ColliderComponent *collider_us = owner->GetComponent<ColliderComponent>();
        ColliderComponent *collider_other = other->GetComponent<ColliderComponent>();
        SDL_FRect a = collider_us->GetWorldBounds();
        SDL_FRect b = collider_other->GetWorldBounds();
        // Calculamos exactamente cuánto están colisionando los objetos
        float overlapX = std::min(a.x + a.w, b.x + b.w) - std::max(a.x, b.x);
        float overlapY = std::min(a.y + a.h, b.y + b.h) - std::max(a.y, b.y);

        // Si no hay solapamiento, no hacemos nada
        if (overlapX <= 0 || overlapY <= 0)
            return;
        // Elegimos el eje de menor penetración
        if (overlapX < overlapY) {
            // Si la pelota está a la izquierda del otro obstáculo (nuestra perspectiva), la pelota debe de desplazarse a la izquierda, indicamos ese sentido
            float direction = (a.x + a.w < b.x + b.w) ? -1.0f : 1.0f;
            // Expulsamos a la pelota a la dirección contraría y cambiamos su velocidad a la dirección contraria
            transform_us->position.x += direction * overlapX;
            velocity.x = -velocity.x;
        }
        else {
            // Si la pelota está arriba del otro obstáculo (nuestra perspectiva), la pelota debe de desplazarse hacia arriba 
            float direction = (a.y + a.h < b.y + b.h) ? -1.0f : 1.0f;
            // Expulsamos a la pelota a la dirección contraría y cambiamos su velocidad a la dirección contraria
            transform_us->position.y += direction * overlapY;
            velocity.y = -velocity.y;
        }

        SDL_Log("Colisión: %s con %s", owner->GetTag().c_str(), other->GetTag().c_str());
    }