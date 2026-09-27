#pragma once

#include <SDL3/SDL.h>

#include "../core/Component.hpp"
#include "../core/GameObject.hpp"
#include "../components/TransformComponent.hpp"
#include "../core/Vector2.hpp"
class RectRenderComponent : public Component
{
    public:
    Vector2 size{60.0f, 60.0f};
    SDL_Color color{60, 180, 100, 255};

    RectRenderComponent() = default;
    RectRenderComponent(Vector2 sz, SDL_Color col) : size(sz), color(col)
    {}

    void Render(SDL_Renderer *renderer) override
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
};