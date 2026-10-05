#include "../../include/Engine/Scene.hpp"

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

void Scene::Render(SDL_Renderer*){}

void Scene::Spawn(std::unique_ptr<GameObject> object){}