#pragma once

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include <SDL3/SDL.h>

#include "Component.hpp"
#include "GameObject.hpp"

// Declaración adelantada
class SceneManager;

class Scene {
protected:
    SceneManager* m_manager{nullptr};
    std::vector<std::unique_ptr<GameObject>> m_entities;
    std::string m_name{"TitleScene"};

public:
    Scene(SceneManager* manager, std::string name)
        : m_manager(manager), m_name(std::move(name)) {}

    virtual ~Scene() = default;

    virtual void Init() {}
    virtual void Exit() {}

    virtual void HandleEvent(const SDL_Event&) {}
    virtual void Update(float dt) {}
    virtual void Render(SDL_Renderer* renderer) {}

    GameObject* CreateGameObject(std::string tag);

    std::vector<std::unique_ptr<GameObject>>& GetEntities();
};