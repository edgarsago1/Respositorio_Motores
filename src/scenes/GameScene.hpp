#pragma once

#include "../core/Scene.hpp"
#include "../managers/CollisionManager.hpp"
#include "../core/GameObject.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RectRenderComponent.hpp"
#include "../components/PlayerControllerComponent.hpp"
#include "../components/PatrolComponent.hpp"
#include "../components/BallComponent.hpp"


class GameScene : public Scene{
  public:
    CollisionManager m_collisionManager;  
    using Scene::Scene;
    float m_physicsAccumulator{0.0f};
    bool m_debugDraw{false};

    void Init(){
        m_entities.clear();
        m_collisionManager.SetEntities(&m_entities);
        // Armamos del Jugador
        auto player = std::make_unique<GameObject>("Player");
        player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
        Vector2{1.0f, 1.0f});
        player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
        SDL_Color{60, 180, 100, 255});
        player->AddComponent<PlayerControllerComponent>(300.0f, true);
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
    void Update(float dt){
        constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
        m_physicsAccumulator += dt;
        while (m_physicsAccumulator >= FIXED_TIMESTEP){
            for (auto &entity : m_entities){
                entity->Update(FIXED_TIMESTEP);
            }
            m_collisionManager.CheckCollisions();
            m_physicsAccumulator -= FIXED_TIMESTEP;
        }
    }

    void HandleEvent(const SDL_Event &event){
        if (event.type == SDL_EVENT_KEY_DOWN){
            if(event.key.key == SDLK_F1){
                m_debugDraw = !m_debugDraw;
                SDL_Log("Debug Draw: %s", m_debugDraw ? "ACTIVADO" : "DESACTIVADO");
            }
            if(event.key.key == SDLK_P || event.key.key == SDLK_ESCAPE){
                m_manager->ShowPause();
            // Por el momento G es tecla de depuración, pero debe de haber una condición de derrota
            } else if(event.key.key == SDLK_G){
                m_manager->ShowGameOver();
            }
        }
    }

    void Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
        SDL_RenderClear(renderer);
        for (auto &entity : m_entities)
            if (auto *square = entity->GetComponent<RectRenderComponent>())
                square->Render(renderer);

        if (m_debugDraw)
            for (auto &entity : m_entities)
                if (auto *col = entity->GetComponent<ColliderComponent>())
                    col->RenderDebug(renderer);
    }

};