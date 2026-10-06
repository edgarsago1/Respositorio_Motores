#pragma once

#include "../Engine/Scene.hpp"
#include "../Physics/CollisionManager.hpp"


class GameScene : public Scene{
  public:
    CollisionManager m_collisionManager;
    std::vector<std::unique_ptr<GameObject>> m_pendingObjects; // Creamos un vector que guarde los objetos a añadir en la escena
    using Scene::Scene;
    float m_physicsAccumulator{0.0f};
    bool m_debugDraw{false};
    bool m_gameOver{false};
    
    void Init() override;
    // Fase de Actualización: La misma que solíamos tener en main
    void Update(float dt) override;

    void HandleEvent(const SDL_Event &event) override;

    void Render(SDL_Renderer *renderer) override;

    // Cada Objeto debe de indicar su deseo de ser eliminado, la escena espera hasta que todos los objetos terminen sus procesos para realizar una eliminación segura
    // Se eliminan todos los objetos con la bandera de Destroyed levantada y todos sus componentes
    void RemoveDestroyedObjects();

    // Para añadir nuevos objetos, seguimos una filosofía similar, creamos un vector con los objetos que queremos insertar en la escena y al final de todos los procesos se añaden de manera segura
    void ProcessPendingObjects();

    // Añade los objetos a la lista de objetos pendientes.
    void Spawn(std::unique_ptr<GameObject> object) override;
};