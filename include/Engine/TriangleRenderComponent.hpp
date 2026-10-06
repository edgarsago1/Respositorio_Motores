#pragma once

#include <SDL3/SDL.h>

#include "Component.hpp"
#include "../Math/Vector2.hpp"
class TriangleRenderComponent : public Component
{
    private:
        bool show{true};
        bool transparent{false};
    public:
        Vector2 size{60.0f, 60.0f};
        SDL_Color color{60, 180, 100, 255};
        SDL_FColor vertexColor = {
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
        };
        TriangleRenderComponent() = default;
        TriangleRenderComponent(Vector2 sz, SDL_Color col) : size(sz), color(col)
        {}

        void setShow(bool new_show);

        void Render(SDL_Renderer *renderer) override;

        void setTransparent(bool new_transparent);
};