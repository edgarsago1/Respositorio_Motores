#pragma once 
#include <memory>
#include "../../include/Engine/Scene.hpp"

class GameOverScene : public Scene{
    public:
        using Scene::Scene;
        void Render(SDL_Renderer *renderer) override;

        void HandleEvent(const SDL_Event &event) override;
};