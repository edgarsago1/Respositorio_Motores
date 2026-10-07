#include "../../include/Engine/AsteroidComponent.hpp"

#include <cmath>
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/ProjectileComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Engine/ExplosionComponent.hpp"
#include "../../include/Physics/ColliderComponent.hpp"
#include "../../include/Engine/Scene.hpp"
#include "../../include/Game/GameScene.hpp"
void AsteroidComponent::FixedUpdate(float fixed_dt){
    if (!owner) return;
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;
    transform->Translate({speed * fixed_dt * direction.x, speed * fixed_dt *direction.y});
    Vector2 max_bounds{960.0f, 540.0f};
    transform->teleportObject(max_bounds, {0.0f, 0.0f});
}

void AsteroidComponent::OnCollision(GameObject *other){
    if (!owner || !other) return;
    if(owner->IsDestroyed()) return;
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    RectRenderComponent *rect = owner->GetComponent<RectRenderComponent>();
    if (!transform || !rect) return;
    ProjectileComponent *projectile_other = other->GetComponent<ProjectileComponent>();
    if (!projectile_other) return;
    // Creamos una explosión en el lugar donde ocurrió la colisión
    if(auto *transform = owner->GetComponent<TransformComponent>()){
            auto explosion = std::make_unique<GameObject>("Explosion");
            explosion->AddComponent<ExplosionComponent>(transform->position, 8);
            owner->GetScene()->Spawn(std::move(explosion));
    }
    if(auto *scene = dynamic_cast<GameScene*>(owner->GetScene())) //Lleva la cuenta de puntuación dentro del manager
            scene->GetRoundManager()->sumScore(stage);
    if(stage > 0){
        Vector2 direction1 = direction.Rotated(20.0f);
        Vector2 direction2 = direction.Rotated(-20.0f);
        auto asteroid1 = std::make_unique<GameObject>("Asteroid");
        asteroid1->AddComponent<TransformComponent>(transform->position);
        asteroid1->AddComponent<AsteroidComponent>(stage-1, Vector2{size.x/2, size.y/2}, direction1, speed*1.3f);
        asteroid1->AddComponent<RectRenderComponent>(Vector2{size.x/2, size.y/2}, rect->color);
        asteroid1->AddComponent<ColliderComponent>(Vector2{size.x/2, size.y/2});
        owner->GetScene()->Spawn(std::move(asteroid1));
        auto asteroid2 = std::make_unique<GameObject>("Asteroid");
        asteroid2->AddComponent<TransformComponent>(transform->position);
        asteroid2->AddComponent<AsteroidComponent>(stage-1, Vector2{size.x/2, size.y/2}, direction2, speed*1.3f);
        asteroid2->AddComponent<RectRenderComponent>(Vector2{size.x/2, size.y/2}, rect->color);
        asteroid2->AddComponent<ColliderComponent>(Vector2{size.x/2, size.y/2});
        owner->GetScene()->Spawn(std::move(asteroid2));
    }
    owner->Destroy();
    
}

int AsteroidComponent::getStage() const{
    return stage;
}