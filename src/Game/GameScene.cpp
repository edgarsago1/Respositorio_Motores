#include "../../include/Game/GameScene.hpp"

#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Engine/TriangleRenderComponent.hpp"
#include "../../include/Engine/ShipControllerComponent.hpp"
#include "../../include/Engine/BallComponent.hpp"
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/PauseScene.hpp"
#include "../../include/Game/GameOverScene.hpp"

    void GameScene::Init(){
            m_entities.clear();
            m_collisionManager.SetEntities(&m_entities);
            // Armamos del Jugador
            auto player = std::make_unique<GameObject>("Player");
            player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
            Vector2{1.0f, 1.0f});
            player->AddComponent<TriangleRenderComponent>(Vector2{120.0f, 120.0f},
            SDL_Color{255, 255, 255, 255});
            player->AddComponent<ShipControllerComponent>(300.0f, 3.0f, false);
            player->AddComponent<ColliderComponent>(Vector2{60.0f, 60.0f});
            m_entities.push_back(std::move(player));

            // Entidad Obstáculo: reutiliza Transform y RectRender sin necesitar PlayerController
            auto obstacle = std::make_unique<GameObject>("Obstacle");
            obstacle->AddComponent<TransformComponent>(Vector2{180.0f, 140.0f},
            Vector2{1.5f, 1.5f});
            obstacle->AddComponent<RectRenderComponent>(Vector2{80.0f, 80.0f},
            SDL_Color{220, 70, 70, 255});
            obstacle->AddComponent<ColliderComponent>(Vector2{80.0f, 80.0f});
            m_entities.push_back(std::move(obstacle));

            auto ball = std::make_unique<GameObject>("Ball");
            ball->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f}, Vector2{1.0f, 1.0f});
            ball->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
            SDL_Color{240, 210, 60, 255});
            ball->AddComponent<ColliderComponent>(Vector2{24.0f, 24.0f});
            ball->AddComponent<BallComponent>();
            m_entities.push_back(std::move(ball));
        }
    // Fase de Actualización: La misma que solíamos tener en main
    void GameScene::Update(float dt){
        constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
        m_physicsAccumulator += dt;
        while (m_physicsAccumulator >= FIXED_TIMESTEP){
            for (auto &entity : m_entities)
                if(entity && entity->IsActive())
                    entity->FixedUpdate(FIXED_TIMESTEP);
            m_collisionManager.CheckCollisions();
            m_physicsAccumulator -= FIXED_TIMESTEP;
        }
        for (auto &entity : m_entities)
            if(entity && entity->IsActive())
                entity->Update(dt);
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
            } else if(event.key.key == SDLK_G){
                m_manager->PushScene(std::make_unique<GameOverScene>(m_manager, "GameOverScene"));

            }
        }
    }

    void GameScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
        SDL_RenderClear(renderer);
        for (auto &entity : m_entities){
            if (auto *square = entity->GetComponent<RectRenderComponent>())
                square->Render(renderer);
            if (auto *triangle = entity->GetComponent<TriangleRenderComponent>())
                triangle->Render(renderer);
        }
        if (m_debugDraw)
            for (auto &entity : m_entities)
                if (auto *col = entity->GetComponent<ColliderComponent>())
                    col->RenderDebug(renderer);
    }