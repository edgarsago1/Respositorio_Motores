#pragma once 

#include "../core/Scene.hpp"

class TitleScene : public Scene{
    public:
        using Scene::Scene;
        void Render(SDL_Renderer *renderer){
            SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
            SDL_RenderClear(renderer);
            SDL_FRect title{280, 215, 400, 110};
            SDL_SetRenderDrawColor(renderer, 34, 113, 179, 255);
            SDL_RenderFillRect(renderer, &title);
            SDL_FRect ready_button{380, 330, 200, 50};
            SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
            SDL_RenderFillRect(renderer, &ready_button);
        }
        void HandleEvent(const SDL_Event &event){
            if (event.type == SDL_EVENT_KEY_DOWN)
                if (event.key.key == SDLK_SPACE || event.key.key == SDLK_RETURN)
                    m_manager->RestartGame();
        }
};