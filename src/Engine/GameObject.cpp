#include "../../include/Engine/GameObject.hpp"

#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <SDL3/SDL.h>

    void GameObject::OnCollision(GameObject *other)
    {
        if (!m_active) return;
        for (auto &component : m_components)
        {
            component->OnCollision(other);
        }
    }
    
    // Propagación del ciclo de vida a todos los componentes hijos
    void GameObject::Update(float dt)
    {
        if (!m_active) return;
        for (auto &component : m_components)
        {
            component->Update(dt);
        }
    }

    void GameObject::Render(SDL_Renderer *renderer)
    {
        if (!m_active) return;
        for (auto &component : m_components)
        {
            component->Render(renderer);
        }
    }