#pragma once 

#include "../../include/Engine/Scene.hpp"

class TitleScene : public Scene{
    public:
        using Scene::Scene;
        void Render(SDL_Renderer *renderer);
        
        void HandleEvent(const SDL_Event &event);
};