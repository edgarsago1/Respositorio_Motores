#pragma once

#include "../Engine/Scene.hpp"
#include "../Physics/CollisionManager.hpp"


class GameScene : public Scene{
  public:
    CollisionManager m_collisionManager;  
    using Scene::Scene;
    float m_physicsAccumulator{0.0f};
    bool m_debugDraw{false};

    void Init() override;
    // Fase de Actualización: La misma que solíamos tener en main
    void Update(float dt) override;

    void HandleEvent(const SDL_Event &event) override;

    void Render(SDL_Renderer *renderer) override;
};