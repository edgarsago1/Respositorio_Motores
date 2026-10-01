#pragma once

#include "../Engine/GameObject.hpp"
#include "ColliderComponent.hpp"

class CollisionManager{
    public:
    std::vector<std::unique_ptr<GameObject>>* m_entities;
    CollisionManager() = default;
    // Constructor del manejador, le damos la lista de los objetos de juego que implementaran físicas.
    explicit CollisionManager(std::vector<std::unique_ptr<GameObject>>*entities): m_entities{entities}{}
    
    void SetEntities(std::vector<std::unique_ptr<GameObject>>* entities);

    // Determina si hay una colisión entre dos objetos
    bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b);

    // Determina si hay una colisión entre dos colisionadores
    bool CheckCollision(const ColliderComponent &a, const ColliderComponent &b);

    void CheckCollisions();
};