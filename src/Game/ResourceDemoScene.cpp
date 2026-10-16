#include "../../include/Game/ResourceDemoScene.hpp"

#include <memory>
#include "../../include/Engine/Components/TransformComponent.hpp"
#include "../../include/Engine/Components/PlayerControllerComponent.hpp"
#include "../../include/Engine/Components/SpriteComponent.hpp"
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Math/Vector2.hpp"

void ResourceDemoScene::Init(){
        m_entities.clear();
        m_collisionManager.SetEntities(&m_entities);
        SDL_Log("Directorio de trabajo: %s", SDL_GetCurrentDirectory());
        auto background = std::make_unique<GameObject>("Background");
        background->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
        auto* background_texture = m_manager->GetResourceManager()->GetTexture("assets/Background.png");
        background->AddComponent<SpriteComponent>(background_texture, 960.0f, 540.f );
        m_entities.push_back(std::move(background));
        auto player = std::make_unique<GameObject>("Player");
        player->AddComponent<TransformComponent>();
        player->AddComponent<PlayerControllerComponent>();
        auto* player_texture = m_manager->GetResourceManager()->GetTexture("assets/Player.png");
        player->AddComponent<SpriteComponent>(player_texture, 100.0f, 50.f );
        m_entities.push_back(std::move(player));
}

void ResourceDemoScene::Update(float dt){
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
        ProcessPendingObjects();
}

void ResourceDemoScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (auto &entity : m_entities)
            if(entity && entity->IsActive() && !entity->IsDestroyed())
                entity->Render(renderer);
        if(m_debugDraw){
            for (auto &entity : m_entities)
                if(entity && entity->IsActive() && !entity->IsDestroyed()){
                    if(auto collider = entity->GetComponent<ColliderComponent>()){
                        collider->RenderDebug(renderer);
                    }
                }
        }
}

void ResourceDemoScene::HandleEvent(const SDL_Event &event){
    if (event.type == SDL_EVENT_KEY_DOWN){
            if(event.key.key == SDLK_SPACE)
                for(int i = 0; i < 10; i++){
                    auto alien = std::make_unique<GameObject>("Alien");
                    alien->AddComponent<TransformComponent>(Vector2{pos_x, pos_y});
                    pos_x += 100.0f;
                    pos_y += 50.0f;
                    if (pos_x > 960.0f) pos_x = 50.0f;
                    if (pos_y > 540.0f) pos_y = 30.0f;
                    auto* alien_texture = m_manager->GetResourceManager()->GetTexture("assets/Enemies.png");
                    alien->AddComponent<SpriteComponent>(alien_texture, 50.0f, 50.f );
                    Spawn(std::move(alien));
                } 
            if(event.key.key == SDLK_C) // SOLO PORQUE LO PIDIÓ LA PRÁCTICA, HACERLO EN EJECUCIÓN PROVOCA POINTER VACÍOS Y COMPORTAMIENTO INDEFINIDO 
                m_manager->GetResourceManager()->Clear();
            if(event.key.key == SDLK_Q){
                SDL_Log("Número de texturas cargadas en VRAM: %lld", m_manager->GetResourceManager()->GetTextureCount());
                SDL_Log("Número de entidades en el juego: %i", m_entities.size());
            } 
    }
}

void ResourceDemoScene::Spawn(std::unique_ptr<GameObject> object){
        object->SetScene(this);
        m_pendingObjects.push_back(std::move(object));
}

void ResourceDemoScene::ProcessPendingObjects(){
        for(auto &obj : m_pendingObjects){
            m_entities.push_back(std::move(obj));
        }
        m_pendingObjects.clear();
}
