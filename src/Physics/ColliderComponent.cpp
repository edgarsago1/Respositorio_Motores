#include "../../include/Physics/ColliderComponent.hpp"

#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp" 
    
    SDL_FRect ColliderComponent::GetWorldBounds() const{
        if (!owner) 
            return SDL_FRect{offset.x, offset.y, size.x, size.y};
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
            if (!transform) 
            return SDL_FRect{offset.x, offset.y, size.x, size.y};
        return SDL_FRect{transform->position.x + offset.x, transform->position.y + offset.y, size.x * transform->scale.x, size.y * transform->scale.y};
    }

    // Dibuja el contorno hueco del colisionador según el estado actual del impacto:
    void ColliderComponent::RenderDebug(SDL_Renderer *renderer){
        SDL_FRect world_bounds = GetWorldBounds();
        if(is_colliding){
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
        }
        SDL_RenderRect(renderer, &world_bounds);
    }
    