#include "../../include/Engine/RectRenderComponent.hpp"

#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"

void RectRenderComponent::Render(SDL_Renderer *renderer)
    {
        if (!owner) return;

        // Consultamos la posición y escala al TransformComponent de nuestra entidad

        TransformComponent *transform = owner->GetComponent<TransformComponent>();

        if (!transform)
        {
            return; // No podemos renderizar si la entidad no tiene posición en el mundo
        }

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_FRect rect{
            transform->position.x,
            transform->position.y,
            size.x * transform->scale.x,
            size.y * transform->scale.y
        };
        SDL_RenderFillRect(renderer, &rect);
    }