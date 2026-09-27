#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "../core/Scene.hpp"

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

public:

    bool HasScenes(){
        return !m_scenes.empty();
    }
    void ChangeScene(std::unique_ptr<Scene> new_scene){
        m_pendingAction = SceneAction::Change;
        m_pendingScene = std::move(new_scene);
    }
    void PushScene(std::unique_ptr<Scene> new_scene){
        m_pendingAction = SceneAction::Push;
        m_pendingScene = std::move(new_scene);
    }

    void PopScene(){
        m_pendingAction = SceneAction::Pop;
    }

    void Clear(){
        for(const auto& scene : m_scenes)
            scene->Exit();
    }

    void ProcessPendingChanges(){
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
    void HandleEvent(const SDL_Event &event){
        if(!m_scenes.empty())
            m_scenes.back()->HandleEvent(event);
    }

    // Solo actualiza el estado de la escena en el tope de la pila
    void Update(float dt){
        if(!m_scenes.empty())
            m_scenes.back()->Update(dt);
    }

    // Hace el render de cada una de las escenas.
    void Render(SDL_Renderer *renderer){
        for(const auto& scene : m_scenes)
            scene->Render(renderer);
    }
    void RestartGame();
    void ShowTitle();
    void ShowGameOver();
    void ShowPause();
};