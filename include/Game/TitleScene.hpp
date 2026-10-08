#pragma once 

#include "../../include/Engine/Scene.hpp"

class TitleScene : public Scene{
    private:
        int change_square_timer{100};
        int current_change_square_timer{100};
    public:
        using Scene::Scene;
        void Render(SDL_Renderer *renderer);
        

        void HandleEvent(const SDL_Event &event);
};