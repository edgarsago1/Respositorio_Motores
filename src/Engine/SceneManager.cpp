#include "../../include/Engine/SceneManager.hpp"

#include <vector>
#include <memory>
#include <utility>
    
    bool SceneManager::HasScenes(){
        return !m_scenes.empty();
    }
    void SceneManager::ChangeScene(std::unique_ptr<Scene> new_scene){
        m_pendingAction = SceneAction::Change;
        m_pendingScene = std::move(new_scene);
    }
    void SceneManager::PushScene(std::unique_ptr<Scene> new_scene){
        m_pendingAction = SceneAction::Push;
        m_pendingScene = std::move(new_scene);
    }

    void SceneManager::PopScene(){
        m_pendingAction = SceneAction::Pop;
    }

    void SceneManager::Clear(){
        for(const auto& scene : m_scenes)
            scene->Exit();
    }

    void SceneManager::ProcessPendingChanges(){
        switch (m_pendingAction){
            case SceneAction::None:
                return;
                break;
            case SceneAction::Change:
                if(!m_scenes.empty()){
                    m_scenes.back()->Exit();
                    m_scenes.pop_back();
                }
                if(m_pendingScene){
                    m_scenes.push_back(std::move(m_pendingScene));
                    m_scenes.back()->Init();
                }
                break;
            case SceneAction::Push:
                if(m_pendingScene){
                    m_scenes.push_back(std::move(m_pendingScene));
                    m_scenes.back()->Init();
                }
                break;
            case SceneAction::Pop:
                if(!m_scenes.empty()){
                    m_scenes.back()->Exit();
                    m_scenes.pop_back();
                }
                break;
            case SceneAction::Clear:
                Clear();
                break;
        }
        m_pendingAction = SceneAction::None;
        m_pendingScene.reset();
    }
    
    // Delega los eventos (input, movimientos, cambios, etc) solo a la escena en el tope de la pila
    void SceneManager::HandleEvent(const SDL_Event &event){
        if(!m_scenes.empty())
            m_scenes.back()->HandleEvent(event);
    }

    // Solo actualiza el estado de la escena en el tope de la pila
    void SceneManager::Update(float dt){
        if(!m_scenes.empty())
            m_scenes.back()->Update(dt);
    }

    // Hace el render de cada una de las escenas.
    void SceneManager::Render(SDL_Renderer *renderer){
        for(const auto& scene : m_scenes)
            scene->Render(renderer);
    }
