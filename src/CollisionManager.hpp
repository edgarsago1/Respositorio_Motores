#pragma once
#include <vector>
#include <memory>
#include <GameObject.hpp>
#include <ColliderComponent.hpp>
class CollisionManager{
    public:
    std::vector<std::unique_ptr<GameObject>>* m_entities;

    // Constructor del manejador, le damos la lista de los objetos de juego que implementaran físicas.
    explicit CollisionManager(std::vector<std::unique_ptr<GameObject>>*entities): m_entities{entities}{}

    // Determina si hay una colisión entre dos objetos
    bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b){
        return (a.x < (b.x + b.w)) && ((a.x + a.w) > b.x) && (a.y < (b.y +b.h)) && ((a.y + a.h) > b.y);
    }

    // Determina si hay una colisión entre dos colisionadores
    bool CheckCollision(const ColliderComponent &a, const ColliderComponent &b){
        return CheckAABB(a.GetWorldBounds(), b.GetWorldBounds());
    }

    void CheckCollisions(){
        // Primera etapa
        for(const auto& entities : *m_entities){
            ColliderComponent *collider = entities->GetComponent<ColliderComponent>();
            if(collider)
                collider->is_colliding=false;
        }
        // Segunda etapa
        for(int i = 0; i < m_entities-> size()-1 ; i++){
            for(int j = i + 1; j < m_entities-> size(); j++){
                ColliderComponent *collider_i = (*m_entities)[i]->GetComponent<ColliderComponent>();
                if(!collider_i)
                    continue;
                ColliderComponent *collider_j = (*m_entities)[j]->GetComponent<ColliderComponent>();
                if(!collider_j)
                    continue;
                if(CheckCollision(*collider_i, *collider_j)){
                    collider_i->is_colliding = true;
                    collider_j->is_colliding = true;
                    (*m_entities)[i]->OnCollision((*m_entities)[j].get());
                    (*m_entities)[j]->OnCollision((*m_entities)[i].get());
                }

            }
        }
    }
};