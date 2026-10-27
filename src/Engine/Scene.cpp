#include "../../include/Engine/Scene.hpp"

#include <algorithm>
#include "../../include/Engine/Components/SpriteComponent.hpp"

Scene::Scene(SceneManager* manager, std::string name)
    : m_manager(manager),
      m_name(std::move(name))
{
}

Scene::~Scene() = default;

void Scene::Init(){}

void Scene::Exit(){}

void Scene::HandleEvent(const SDL_Event&){}

void Scene::Update(float){}

void Scene::FixedUpdate(float fixed_dt){}

void Scene::Render(SDL_Renderer* renderer){
    std::vector<GameObject *>renderQueue;
    for(auto &entity : m_entities){
      if(entity && (!entity->IsActive() || entity->IsDestroyed()))
          continue;
      renderQueue.push_back(entity.get());
      }
      std::stable_sort(renderQueue.begin(), renderQueue.end(), [](const GameObject *a, const GameObject *b) {
      int layerA = 0;
      int layerB = 0;
      if (auto *spriteA = a->GetComponent<SpriteComponent>()) layerA = spriteA->GetLayer();
      if (auto *spriteB = b->GetComponent<SpriteComponent>()) layerB = spriteB->GetLayer();
      return layerA < layerB;
    });
    for(GameObject *entity : renderQueue)
        entity->Render(renderer);
    
}

void Scene::Spawn(std::unique_ptr<GameObject> object){}