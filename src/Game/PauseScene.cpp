#include "../../include/Game/PauseScene.hpp"

#include "../../include/Engine/SceneManager.hpp"
    void PauseScene::HandleEvent(const SDL_Event &event){
        if (event.type == SDL_EVENT_KEY_DOWN)
            if(event.key.key == SDLK_P || event.key.key == SDLK_ESCAPE)
                m_manager->PopScene();
    }

    void PauseScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175); // Alfa = 175
        SDL_FRect screen_overlay{0.0f, 0.0f, 960.0f, 540.0f};
        SDL_RenderFillRect(renderer, &screen_overlay);
        //  Rectángulo de centro 
        SDL_FRect pause_square{430, 245, 100, 50};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pause_square);
        //  Rectángulo para hacer el símbolo de pausa.
        SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
        SDL_FRect pause_i{450, 255, 22, 31};
        SDL_RenderFillRect(renderer, &pause_i);
        SDL_FRect pause_ii{490, 255, 22, 31};
        SDL_RenderFillRect(renderer, &pause_ii);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }