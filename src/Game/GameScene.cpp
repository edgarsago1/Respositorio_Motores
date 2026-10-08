#include "../../include/Game/GameScene.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Engine/TriangleRenderComponent.hpp"
#include "../../include/Engine/ShipControllerComponent.hpp"
#include "../../include/Engine/AsteroidComponent.hpp"
#include "../../include/Engine/ExplosionComponent.hpp"
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/PauseScene.hpp"
#include "../../include/Game/GameOverScene.hpp"


    void GameScene::Init(){
            m_entities.clear();
            m_collisionManager.SetEntities(&m_entities);
            m_roundManager.SetScene(this);
            // Armamos del Jugador
            auto player = std::make_unique<GameObject>("Player");
            player->SetScene(this);
            player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
            Vector2{1.0f, 1.0f});
            player->AddComponent<TriangleRenderComponent>(Vector2{70.0f, 70.0f},
            SDL_Color{255, 255, 255, 255});
            player->AddComponent<ShipControllerComponent>(300.0f, 3.0f, 20, true);
            player->AddComponent<ColliderComponent>(Vector2{22.0f, 22.0f});
            m_entities.push_back(std::move(player));
            m_roundManager.SetShip(dynamic_cast<ShipControllerComponent*>(m_entities.back()->GetComponent<ShipControllerComponent>()));
            // Entidad Obstáculo: reutiliza Transform y RectRender sin necesitar PlayerController
        }
    // Fase de Actualización: La misma que solíamos tener en main
    void GameScene::Update(float dt){
        constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
        m_physicsAccumulator += dt;
        while (m_physicsAccumulator >= FIXED_TIMESTEP){
            for (auto &entity : m_entities)
                if(entity && entity->IsActive() && !entity->IsDestroyed()){
                    entity->FixedUpdate(FIXED_TIMESTEP);
                }
            m_collisionManager.CheckCollisions();
            m_physicsAccumulator -= FIXED_TIMESTEP;
        }
        for (auto &entity : m_entities)
            if(entity && entity->IsActive() && !entity->IsDestroyed())
                entity->Update(dt);
        RemoveDestroyedObjects();
        ProcessPendingObjects();
        m_roundManager.manageRounds();
        if (m_roundManager.IsDefeated()){
            m_manager->PushScene(std::make_unique<GameOverScene>(m_manager, "GameOverScene"));
            SDL_Log("Score Obtenido: %i", m_roundManager.getFinalScore());
        }
    }

    void GameScene::HandleEvent(const SDL_Event &event){
        
        if (event.type == SDL_EVENT_KEY_DOWN){
            if(event.key.key == SDLK_F1){
                m_debugDraw = !m_debugDraw;
                SDL_Log("Debug Draw: %s", m_debugDraw ? "ACTIVADO" : "DESACTIVADO");
            }
            if(event.key.key == SDLK_P || event.key.key == SDLK_ESCAPE){
                m_manager->PushScene(std::make_unique<PauseScene>(m_manager, "PauseScene"));
            // Por el momento G es tecla de depuración, pero debe de haber una condición de derrota
            } else if(event.key.key == SDLK_1){
                for(auto &entity : m_entities)
                    if(auto *player = entity->GetComponent<ShipControllerComponent>()){
                        player->changeControllers();
                        SDL_Log("Changed Controllers");
                        break;
                    }
            }
        }
    }

    void GameScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (auto &entity : m_entities){
            if(entity->IsDestroyed() || !entity->IsActive())
                continue;
            if (auto *square = entity->GetComponent<RectRenderComponent>())
                square->Render(renderer);
            if (auto *triangle = entity->GetComponent<TriangleRenderComponent>())
                triangle->Render(renderer);
            if (auto *explosion = entity->GetComponent<ExplosionComponent>()) // Ahora se dibujan particular a la hora de impactarse la nave o algún asteroide.
                explosion->Render(renderer);
        }
        if (m_debugDraw)
            for (auto &entity : m_entities){
                if(entity->IsDestroyed() || !entity->IsActive())
                    continue;
                if (auto *col = entity->GetComponent<ColliderComponent>())
                    col->RenderDebug(renderer);
            }
    }

    void GameScene::RemoveDestroyedObjects(){
        std::erase_if(m_entities, [](const std::unique_ptr<GameObject>& object){
            return object->IsDestroyed();
        });
}

    void GameScene::Spawn(std::unique_ptr<GameObject> object){
        object->SetScene(this);
        m_pendingObjects.push_back(std::move(object));
    }
    
    //Determina si hay enemigos en la escena, tanto en los objetos activos como en los pendientes de añadir
    bool GameScene::StillEnemiesLeft() const{
        for (auto &entity : m_entities){
                if(!entity || entity->IsDestroyed() || !entity->IsActive())
                    continue;
                if(auto *asteroid = entity->GetComponent<AsteroidComponent>()){
                    return true;
                }
        }
        for(auto &entity : m_pendingObjects){
                if(!entity || entity->IsDestroyed() || !entity->IsActive())
                    continue;
                if(auto *asteroid = entity->GetComponent<AsteroidComponent>()){
                    return true;
                }
        }
        return false;
    }
    void GameScene::ProcessPendingObjects(){
        for(auto &obj : m_pendingObjects){
            m_entities.push_back(std::move(obj));
        }
        m_pendingObjects.clear();
    }
