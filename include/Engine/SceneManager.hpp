#pragma once

#include "Scene.hpp"
#include "ResourceManager.hpp"
enum class SceneAction {
    None,
    Change,
    Push, 
    Pop,
    Clear
};

class SceneManager{
private:
    std::vector<std::unique_ptr<Scene>> m_scenes;
    SceneAction m_pendingAction{SceneAction::None};
    std::unique_ptr<Scene> m_pendingScene{nullptr};
    SDL_Window* window{nullptr};
    ResourceManager* m_resource_manager{nullptr};
public:

    void SetWindow(SDL_Window* win){
        window = win;
    }

    // Le da un apuntador del administrador de recursos al manager para comunicación con escenas, pero por reglas, scenemanager no puede modificar al manager
    void SetResourceManager(ResourceManager* manager){
        m_resource_manager = manager;
    }

    bool HasScenes();

    void ChangeScene(std::unique_ptr<Scene> new_scene);

    void PushScene(std::unique_ptr<Scene> new_scene);

    void PopScene();

    void Clear();

    void ProcessPendingChanges();
    
    // Delega los eventos (input, movimientos, cambios, etc) solo a la escena en el tope de la pila
    void HandleEvent(const SDL_Event &event);

    // Solo actualiza el estado de la escena en el tope de la pila
    void Update(float dt);

    // Hace el render de cada una de las escenas.
    void Render(SDL_Renderer *renderer);

    SDL_Window* GetWindow() const;

    ResourceManager* GetResourceManager() const;
};