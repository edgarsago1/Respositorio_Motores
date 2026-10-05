#pragma once

#include "Component.hpp"
#include <string>
#include <memory>
#include <vector>
class Scene;

class GameObject
{
private:
    std::vector<std::unique_ptr<Component>> m_components;
    std::string m_tag{"GameObject"};
    bool m_active{true};
    bool m_destroyed{false};
    Scene* m_scene{nullptr};
public:
    GameObject() = default;
    explicit GameObject(std::string tag) : m_tag(std::move(tag)) {}
    ~GameObject() = default;

    // Deshabilitar copia para garantizar la propiedad estricta de unique_ptr
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) = delete;

    // Habilitar movimiento en memoria
    GameObject(GameObject &&) noexcept = default;
    GameObject &operator=(GameObject &&) noexcept = default;

    // Identificación y estado
    const std::string &GetTag() const { return m_tag; }
    void SetTag(std::string tag) { m_tag = std::move(tag); }
    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }

    bool IsDestroyed() const { return m_destroyed; }
    void SetScene(Scene* scene){
        m_scene = scene;
    }

    Scene* GetScene() const{
        return m_scene;
    }
    // Para armar componentes con reenvío perfecto
    template <typename T, typename... Args> T *AddComponent(Args &&...args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T debe derivar de Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->owner = this;
        component->Init();
        T *ptr = component.get();
        m_components.push_back(std::move(component));
        return ptr;
    }

    // Consulta de componentes
    template <typename T> T *GetComponent() const
    {
        static_assert(std::is_base_of_v<Component, T>, "T debe derivar de Component");

        for (const auto &component : m_components)
        {
            if (auto casted = dynamic_cast<T *>(component.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    template <typename T> bool HasComponent() const
    {
        return GetComponent<T>() != nullptr;
    }

    void OnCollision(GameObject *other);

    // Se declara Update, pero por el momento no se usa en los gameObjects que tenemos disponibles.
    void Update(float dt);
    
    void FixedUpdate(float fixed_dt);

    void Render(SDL_Renderer *renderer);

    std::unique_ptr<GameObject> Clone(const std::string &new_tag) const;

    // Usamos una bandera para señalar a la escena y manejador de colisiones que este GameObject será destruido
    void Destroy(){
        m_destroyed = true;
    }
};