#pragma once

#include <vector>
#include <string>
#include <memory>

#include <SDL3/SDL.h>

#include "GameObject.hpp"

class SceneManager;

class Scene
{
protected:
    SceneManager* m_manager{nullptr};
    std::vector<std::unique_ptr<GameObject>> m_entities;
    std::string m_name{"TitleScene"};

public:
    Scene(SceneManager* manager, std::string name);
    virtual ~Scene();

    virtual void Init();
    virtual void Exit();

    virtual void HandleEvent(const SDL_Event&);

    virtual void Update(float dt);

    virtual void FixedUpdate(float fixed_dt);
    
    virtual void Render(SDL_Renderer* renderer);

    GameObject* CreateGameObject(std::string tag);

    std::vector<std::unique_ptr<GameObject>>& GetEntities();

    // Una función que inserta un objeto y sus componentes a la escena, recibe un objeto y lo añade dentro de m_entities
    virtual void Spawn(std::unique_ptr<GameObject> object);
};