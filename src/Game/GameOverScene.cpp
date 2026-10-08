#include "../../include/Game/GameOverScene.hpp"

#include <memory>
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/GameScene.hpp"
#include "../../include/Game/TitleScene.hpp"

        void GameOverScene::Render(SDL_Renderer *renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // Game Over
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

            SDL_FRect g1{282, 216, 8, 34};
            SDL_RenderFillRect(renderer, &g1);
            SDL_FRect g2{282, 216, 32, 7};
            SDL_RenderFillRect(renderer, &g2);
            SDL_FRect g3{282, 244, 31.6f, 6.5f};
            SDL_RenderFillRect(renderer, &g3);
            SDL_FRect g4{305.6f, 230.17f, 9.3f, 20};
            SDL_RenderFillRect(renderer, &g4);
            SDL_FRect g5{300, 230, 8, 7.28f};
            SDL_RenderFillRect(renderer, &g5);

            SDL_FRect a1{320, 216, 10.2f, 32.6f};
            SDL_RenderFillRect(renderer, &a1);
            SDL_FRect a2{341, 217, 10.2f, 32.6f};
            SDL_RenderFillRect(renderer, &a2);

            SDL_FRect a3{328, 216, 15, 7};
            SDL_RenderFillRect(renderer, &a3);
            SDL_FRect a4{328, 230, 15, 6};
            SDL_RenderFillRect(renderer, &a4);

            SDL_FRect m1{363, 216, 9, 34};
            SDL_RenderFillRect(renderer, &m1);
            SDL_FRect m2{397, 216, 9, 34};
            SDL_RenderFillRect(renderer, &m2);
            SDL_FRect m3{372, 216, 8, 12};
            SDL_RenderFillRect(renderer, &m3);
            SDL_FRect m4{389, 216, 8, 12};
            SDL_RenderFillRect(renderer, &m4);
            SDL_FRect m5{379, 224, 11, 12};
            SDL_RenderFillRect(renderer, &m5);

            SDL_FRect e1{419, 216, 9, 34};
            SDL_RenderFillRect(renderer, &e1);
            SDL_FRect e2{428, 216, 21, 7};
            SDL_RenderFillRect(renderer, &e2);
            SDL_FRect e3{428, 230, 17, 6};
            SDL_RenderFillRect(renderer, &e3);
            SDL_FRect e4{428, 244, 21, 6};
            SDL_RenderFillRect(renderer, &e4);
            //  ESPACIO 
            SDL_FRect o1{469, 216, 9, 34};
            SDL_RenderFillRect(renderer, &o1);
            SDL_FRect o2{501, 216, 9, 34};
            SDL_RenderFillRect(renderer, &o2);
            SDL_FRect o3{478, 216, 23, 7};
            SDL_RenderFillRect(renderer, &o3);
            SDL_FRect o4{478, 244, 23, 6};
            SDL_RenderFillRect(renderer, &o4);

            SDL_FRect v1{526, 216, 9, 21};
            SDL_RenderFillRect(renderer, &v1);
            SDL_FRect v2{550, 216, 9, 21};
            SDL_RenderFillRect(renderer, &v2);
            SDL_FRect v3{533, 236, 9, 7};
            SDL_RenderFillRect(renderer, &v3);
            SDL_FRect v4{543, 236, 9, 7};
            SDL_RenderFillRect(renderer, &v4);
            SDL_FRect v5{538, 243, 7, 7};
            SDL_RenderFillRect(renderer, &v5);

            SDL_FRect ev1{577, 216, 9, 34};
            SDL_RenderFillRect(renderer, &ev1);
            SDL_FRect ev2{586, 216, 21, 7};
            SDL_RenderFillRect(renderer, &ev2);
            SDL_FRect ev3{586, 230, 17, 6};
            SDL_RenderFillRect(renderer, &ev3);
            SDL_FRect ev4{586, 244, 21, 6};
            SDL_RenderFillRect(renderer, &ev4);

            SDL_FRect r1{619, 216, 9, 34};
            SDL_RenderFillRect(renderer, &r1);
            SDL_FRect r2{628, 216, 21, 7};
            SDL_RenderFillRect(renderer, &r2);
            SDL_FRect r3{628, 230, 21, 7};
            SDL_RenderFillRect(renderer, &r3);
            SDL_FRect r4{644, 221, 8, 12};
            SDL_RenderFillRect(renderer, &r4);
            SDL_FRect r5{639, 234, 13, 16};
            SDL_RenderFillRect(renderer, &r5);

            //Palabra Retry
            SDL_FRect r_1{365, 316, 9, 34};
            SDL_RenderFillRect(renderer, &r_1);
            SDL_FRect r_2{374, 316, 21, 7};
            SDL_RenderFillRect(renderer, &r_2);
            SDL_FRect r_3{374, 330, 21, 7};
            SDL_RenderFillRect(renderer, &r_3);
            SDL_FRect r_4{390, 321, 8, 12};
            SDL_RenderFillRect(renderer, &r_4);
            SDL_FRect r_5{385, 334, 13, 16};
            SDL_RenderFillRect(renderer, &r_5);

            SDL_FRect e_1{407, 316, 9, 34};
            SDL_RenderFillRect(renderer, &e_1);
            SDL_FRect e_2{416, 316, 21, 7};
            SDL_RenderFillRect(renderer, &e_2);
            SDL_FRect e_3{416, 330, 17, 6};
            SDL_RenderFillRect(renderer, &e_3);
            SDL_FRect e_4{416, 344, 21, 6};
            SDL_RenderFillRect(renderer, &e_4);

            SDL_FRect t1{451, 316, 23, 7};
            SDL_RenderFillRect(renderer, &t1);
            SDL_FRect t2{458, 316, 9, 34};
            SDL_RenderFillRect(renderer, &t2);

            SDL_FRect r6{486, 316, 9, 34};
            SDL_RenderFillRect(renderer, &r6);
            SDL_FRect r7{495, 316, 21, 7};
            SDL_RenderFillRect(renderer, &r7);
            SDL_FRect r8{495, 330, 21, 7};
            SDL_RenderFillRect(renderer, &r8);
            SDL_FRect r9{511, 321, 8, 12};
            SDL_RenderFillRect(renderer, &r9);
            SDL_FRect r10{506, 334, 13, 16};
            SDL_RenderFillRect(renderer, &r10);

            SDL_FRect y1{528, 316, 9, 17};
            SDL_RenderFillRect(renderer, &y1);
            SDL_FRect y2{546, 316, 9, 17};
            SDL_RenderFillRect(renderer, &y2);
            SDL_FRect y3{537, 330, 9, 20};
            SDL_RenderFillRect(renderer, &y3);

            // Botón a pulsar
            SDL_FRect sep_r{570, 319, 4, 28};
            SDL_RenderFillRect(renderer, &sep_r);
            SDL_FRect ind_r1{588, 316, 8, 34};
            SDL_RenderFillRect(renderer, &ind_r1);
            SDL_FRect ind_r2{596, 316, 18, 6};
            SDL_RenderFillRect(renderer, &ind_r2);
            SDL_FRect ind_r3{596, 330, 18, 6};
            SDL_RenderFillRect(renderer, &ind_r3);
            SDL_FRect ind_r4{610, 321, 7, 12};
            SDL_RenderFillRect(renderer, &ind_r4);
            SDL_FRect ind_r5{605, 334, 12, 16};
            SDL_RenderFillRect(renderer, &ind_r5);

            // Palabra Menu 
            SDL_FRect mn1{365, 395, 9, 34};
            SDL_RenderFillRect(renderer, &mn1);
            SDL_FRect mn2{399, 395, 9, 34};
            SDL_RenderFillRect(renderer, &mn2);
            SDL_FRect mn3{374, 395, 8, 12};
            SDL_RenderFillRect(renderer, &mn3);
            SDL_FRect mn4{391, 395, 8, 12};
            SDL_RenderFillRect(renderer, &mn4);
            SDL_FRect mn5{381, 403, 11, 12};
            SDL_RenderFillRect(renderer, &mn5);

            SDL_FRect en1{421, 395, 9, 34};
            SDL_RenderFillRect(renderer, &en1);
            SDL_FRect en2{430, 395, 21, 7};
            SDL_RenderFillRect(renderer, &en2);
            SDL_FRect en3{430, 409, 17, 6};
            SDL_RenderFillRect(renderer, &en3);
            SDL_FRect en4{430, 423, 21, 6};
            SDL_RenderFillRect(renderer, &en4);

            SDL_FRect nn1{461, 395, 9, 34};
            SDL_RenderFillRect(renderer, &nn1);
            SDL_FRect nn2{493, 395, 9, 34};
            SDL_RenderFillRect(renderer, &nn2);
            SDL_FRect nn3{470, 399, 10, 10};
            SDL_RenderFillRect(renderer, &nn3);
            SDL_FRect nn4{480, 411, 10, 10};
            SDL_RenderFillRect(renderer, &nn4);

            SDL_FRect un1{515, 395, 9, 34};
            SDL_RenderFillRect(renderer, &un1);
            SDL_FRect un2{543, 395, 9, 34};
            SDL_RenderFillRect(renderer, &un2);
            SDL_FRect un3{524, 422, 20, 7};
            SDL_RenderFillRect(renderer, &un3);
            // Pulsar M
            SDL_FRect sep_m{570, 398, 4, 28};
            SDL_RenderFillRect(renderer, &sep_m);

            SDL_FRect ind_m1{588, 395, 8, 34};
            SDL_RenderFillRect(renderer, &ind_m1);
            SDL_FRect ind_m2{618, 395, 8, 34};
            SDL_RenderFillRect(renderer, &ind_m2);
            SDL_FRect ind_m3{594, 395, 7, 11};
            SDL_RenderFillRect(renderer, &ind_m3);
            SDL_FRect ind_m4{613, 395, 7, 11};
            SDL_RenderFillRect(renderer, &ind_m4);
            SDL_FRect ind_m5{602, 402, 10, 11};
            SDL_RenderFillRect(renderer, &ind_m5);

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