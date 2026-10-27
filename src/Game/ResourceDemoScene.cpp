#include "../../include/Game/ResourceDemoScene.hpp"

#include <memory>
#include "../../include/Engine/Components/TransformComponent.hpp"
#include "../../include/Engine/Components/PlayerControllerComponent.hpp"
#include "../../include/Engine/Components/SpriteComponent.hpp"
#include "../../include/Engine/Components/AnimationComponent.hpp"
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Engine/Camera2D.hpp"
#include "../../include/Math/Vector2.hpp"

void ResourceDemoScene::Init(){
        m_entities.clear();
        m_collisionManager.SetEntities(&m_entities);
        SDL_Log("Directorio de trabajo: %s", SDL_GetCurrentDirectory());
        m_camera.SetPosition({0.0f, 0.0f});
        m_camera.SetBounds(Vector2{0,0}, Vector2{1440, 0});
        float pos_x = -960.0;
        for (int i = 0; i < 4; i ++ ){
            // Sky 
            auto sky = std::make_unique<GameObject>("Sky");
            sky->AddComponent<TransformComponent>(Vector2{pos_x, 0.0f});
            auto* sky_texture = m_manager->GetResourceManager()->GetTexture("assets/bg_sky.png");
            auto* sky_sprite = sky->AddComponent<SpriteComponent>(sky_texture, 960.0f, 540.f );
            sky_sprite->SetLayer(-30);
            sky_sprite->SetParallaxFactor(Vector2{0.05f, 0.0f});
            m_entities.push_back(std::move(sky));
            // Mountains
            auto mountains = std::make_unique<GameObject>("Mountains");
            mountains->AddComponent<TransformComponent>(Vector2{pos_x, 200.0f});
            auto* mountains_texture = m_manager->GetResourceManager()->GetTexture("assets/bg_mountains.png");
            auto* mountains_sprite = mountains->AddComponent<SpriteComponent>(mountains_texture, 960.0f, 400.f );
            mountains_sprite->SetLayer(-20);
            mountains_sprite->SetParallaxFactor(Vector2{0.25f, 0.0f});
            m_entities.push_back(std::move(mountains));
            // ground
            auto ground = std::make_unique<GameObject>("ground");
            ground->AddComponent<TransformComponent>(Vector2{pos_x, 450.0f});
            auto* ground_texture = m_manager->GetResourceManager()->GetTexture("assets/ground.png");
            auto* ground_sprite = ground->AddComponent<SpriteComponent>(ground_texture, 960.0f, 90.f );
            ground_sprite->SetLayer(0);
            ground_sprite->SetParallaxFactor(Vector2{1.0f, 1.0f});
            m_entities.push_back(std::move(ground));
            pos_x += 960.0f;
        }
        //Trees
        pos_x = 0.0;
        for (int i = 0; i < 13; i ++ ){
            auto tree = std::make_unique<GameObject>("tree");
            tree->AddComponent<TransformComponent>(Vector2{pos_x, 70.0f});
            auto* tree_texture = m_manager->GetResourceManager()->GetTexture("assets/bg_trees.png");
            auto* tree_sprite = tree->AddComponent<SpriteComponent>(tree_texture, 200.0f, 400.f );
            tree_sprite->SetLayer(-10);
            tree_sprite->SetParallaxFactor(Vector2{0.5f, 0.0f});
            m_entities.push_back(std::move(tree));
            pos_x += 200.0f;
        }
        // Enemy 
        auto enemy = std::make_unique<GameObject>("enemy");
        enemy->AddComponent<TransformComponent>(Vector2{2000.0f, 450.0f});
        auto* enemy_texture = m_manager->GetResourceManager()->GetTexture("assets/enemy.png");
        auto* enemy_sprite = enemy->AddComponent<SpriteComponent>(enemy_texture, 50.0f, 50.0f );
        enemy_sprite->SetLayer(5);
        enemy_sprite->SetParallaxFactor(Vector2{1.0f, 1.0f});
        m_entities.push_back(std::move(enemy));
        // Player 
        auto player = std::make_unique<GameObject>("player");
        auto* playerTransform = player->AddComponent<TransformComponent>(Vector2{0.0f, 400.0f});
        auto* player_texture = m_manager->GetResourceManager()->GetTexture("assets/player.png");
        auto* player_sprite = player->AddComponent<SpriteComponent>(player_texture, 50.0f, 100.f );
        player_sprite->SetLayer(10);
        auto* animation = player->AddComponent<AnimationComponent>(
            23,60, 6, 4, 4, 6
        );
        animation->AddClip(
            "Walk",     // Nombre
            1,          // Fila
            4,          // Total de frames
            0.25f,      // Duración de cada frame, en segundos
            true,        // Repetir en bucle
            6     // Starter frame
        );
        animation->AddClip(
            "Idle",     // Nombre
            0,          // Fila
            4,          // Total de frames
            0.25f,      // Duración de cada frame, en segundos
            true,        // Repetir en bucle
            0     // Starter frame
        );
        m_playerTransform = playerTransform;
        player->AddComponent<PlayerControllerComponent>();
        m_entities.push_back(std::move(player));
        // Placeholder de un HUD
        auto HUD = std::make_unique<GameObject>("HUD");
            HUD->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
            auto* HUD_texture = m_manager->GetResourceManager()->GetTexture("assets/HUD.png");
            auto* HUD_sprite = HUD->AddComponent<SpriteComponent>(HUD_texture, 300.0f, 200.0f );
            HUD_sprite->SetLayer(100);
            HUD_sprite->SetAffectedByCamera(false);
            m_entities.push_back(std::move(HUD));
        
        m_camera.SetFollowHorizontal(true);
        m_camera.SetFollowVertical(false);
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
        m_camera.Follow(Vector2{m_playerTransform->position.x + 25.0f, m_playerTransform->position.y + 50.0f }, 4.5f, dt);
        ProcessPendingObjects();
}

void ResourceDemoScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Scene::Render(renderer);
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
