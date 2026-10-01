#pragma once
#include "../Engine/Component.hpp"
#include "../Math/Vector2.hpp"
 
class ColliderComponent : public Component{
    public:
    Vector2 offset{0.0f, 0.0f};
    Vector2 size{60.0f, 60.0f};
    bool is_trigger{false};
    bool is_colliding{false};

    ColliderComponent(Vector2 custom_size): size{custom_size}{}
    
    // Calcula y devuelve la caja de colisión en coordenadas absolutas de pantalla:
    SDL_FRect GetWorldBounds() const;

    // Dibuja el contorno hueco del colisionador según el estado actual del impacto:
    void RenderDebug(SDL_Renderer *renderer);
};