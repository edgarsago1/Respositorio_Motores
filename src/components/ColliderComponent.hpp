#pragma once
#include "../core/Component.hpp"
#include "../core/Vector2.hpp"
#include "../components/TransformComponent.hpp"
#include "../core/GameObject.hpp"  
class ColliderComponent : public Component{
    public:
    Vector2 offset{0.0f, 0.0f};
    Vector2 size{60.0f, 60.0f};
    bool is_trigger{false};
    bool is_colliding{false};

    ColliderComponent(Vector2 custom_size): size{custom_size}{}
    
    // Calcula y devuelve la caja de colisión en coordenadas absolutas de pantalla:
    SDL_FRect GetWorldBounds() const{
        if (!owner) 
            return SDL_FRect{offset.x, offset.y, size.x, size.y};
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
            if (!transform) 
            return SDL_FRect{offset.x, offset.y, size.x, size.y};
        return SDL_FRect{transform->position.x + offset.x, transform->position.y + offset.y, size.x * transform->scale.x, size.y * transform->scale.y};
    }

    // Dibuja el contorno hueco del colisionador según el estado actual del impacto:
    void RenderDebug(SDL_Renderer *renderer){
        SDL_FRect world_bounds = GetWorldBounds();
        if(is_colliding){
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
        }
        SDL_RenderRect(renderer, &world_bounds);
    }
    
};