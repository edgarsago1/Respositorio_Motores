#include "../../include/Game/GameOverScene.hpp"

#include <memory>
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/GameScene.hpp"
#include "../../include/Game/TitleScene.hpp"

        void GameOverScene::Render(SDL_Renderer *renderer){
            SDL_SetRenderDrawColor(renderer, 45, 15, 20, 255);
            SDL_RenderClear(renderer);
            // Crucifijo de GAMEOVER
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
            SDL_FRect cross_hor{410, 110, 141, 30};
            SDL_RenderFillRect(renderer, &cross_hor);
            SDL_FRect cross_ver{466, 52, 27.5f, 213};
            SDL_RenderFillRect(renderer, &cross_ver);
            // Los botones que por el momento no hacen nada
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_FRect reiniciar{430, 270, 100, 50};
            SDL_RenderFillRect(renderer, &reiniciar);
            SDL_SetRenderDrawColor(renderer, 83, 83, 236, 255);
            SDL_FRect menu{430, 380, 100, 50};
            SDL_RenderFillRect(renderer, &menu);
        }

        void GameOverScene::HandleEvent(const SDL_Event &event){
            if (event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_R){
                    m_manager->ChangeScene(std::make_unique<GameScene>(m_manager, "GameScene"));
                } else if (event.key.key == SDLK_M || event.key.key == SDLK_ESCAPE){
                    m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager, "TitleScene"));
                }
            }
        }