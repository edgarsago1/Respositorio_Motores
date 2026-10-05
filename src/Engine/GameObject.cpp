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
        if (!m_active || m_destroyed) return;
        for (auto &component : m_components)
        {
            component->Update(dt);
        }
    }

    //
    void GameObject::FixedUpdate(float fixed_dt){
        if (!m_active || m_destroyed) return;
        for (auto &component : m_components)
        {
            component->FixedUpdate(fixed_dt);
        }
    }

    void GameObject::Render(SDL_Renderer *renderer)
    {
        if (!m_active || m_destroyed) return;
        for (auto &component : m_components)
        {
            component->Render(renderer);
        }
    }

    std::unique_ptr<GameObject> GameObject::Clone(const std::string &new_tag) const{ 
        auto cloned_object = std::make_unique<GameObject>(new_tag);
        cloned_object->m_active = m_active;
        cloned_object->m_destroyed = m_destroyed;
        for(const auto &comp : m_components)
            if(comp){
                auto cloned_comp = comp->Clone();
                cloned_comp->owner = cloned_object.get();
                cloned_object->m_components.push_back(std::move(cloned_comp));
            }
        return cloned_object;
    }