#include "../../include/Game/TitleScene.hpp"

#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/GameScene.hpp"

    void TitleScene::Render(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
        SDL_RenderClear(renderer);
        SDL_FRect title{280, 215, 400, 110};
        SDL_SetRenderDrawColor(renderer, 34, 113, 179, 255);
        SDL_RenderFillRect(renderer, &title);
        SDL_FRect ready_button{380, 330, 200, 50};
        SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
        SDL_RenderFillRect(renderer, &ready_button);
    }

   void TitleScene::HandleEvent(const SDL_Event &event){
        if (event.type == SDL_EVENT_KEY_DOWN)
            if (event.key.key == SDLK_SPACE || event.key.key == SDLK_RETURN)
                m_manager->ChangeScene(std::make_unique<GameScene>(m_manager, "GameScene"));
    }