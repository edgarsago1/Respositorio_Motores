#pragma once

#include "../../include/engine/Scene.hpp"

class PauseScene : public Scene{
    public:
        using Scene::Scene;
        void HandleEvent(const SDL_Event &event);

        void Render(SDL_Renderer *renderer);
};