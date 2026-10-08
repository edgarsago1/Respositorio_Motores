#include "../../include/Game/TitleScene.hpp"

#include <random>
#include "../../include/Engine/SceneManager.hpp"
#include "../../include/Game/GameScene.hpp"
std::random_device rdm;
std::mt19937 generator1(rdm());
std::uniform_int_distribution<int> distribution_color(20, 255);
std::uniform_real_distribution<float> size_square(50.0f, 110.0f); 
SDL_Color color_title{40, 50, 100, 255};
SDL_FRect rect1 = SDL_FRect{600, 100, size_square(generator1), size_square(generator1)};
SDL_Vertex decorativeTriangleVertex[3];

    void TitleScene::Render(SDL_Renderer *renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // Figuras decorativas. Un cuadradito que cambia de color y tamaño cada cierto tiempo.
            if (current_change_square_timer <= 0){
                color_title.r = static_cast<Uint8>(distribution_color(generator1));
                color_title.g = static_cast<Uint8>(distribution_color(generator1));
                color_title.b = static_cast<Uint8>(distribution_color(generator1));
                float size_square1 = size_square(generator1);
                float size_square2 = size_square(generator1);
                rect1 = SDL_FRect{600, 100, size_square(generator1), size_square(generator1)};
                SDL_SetRenderDrawColor(renderer, color_title.r, color_title.g, color_title.b, color_title.a);
                current_change_square_timer = change_square_timer;
            } else {
                current_change_square_timer--;
            }
            SDL_SetRenderDrawColor(renderer, color_title.r, color_title.g, color_title.b, color_title.a);
            SDL_RenderFillRect(renderer, &rect1);
            // Figura decorativa: Un triángulo fijo 
            SDL_FColor white_Color = SDL_FColor{1.0f, 1.0f, 1.0f, 1.0f}; 
            decorativeTriangleVertex[0] = {180, 210};
            decorativeTriangleVertex[0].color = white_Color;
            decorativeTriangleVertex[1] = {180, 300};
            decorativeTriangleVertex[1].color = white_Color;
            decorativeTriangleVertex[2] = {260, 250};
            decorativeTriangleVertex[2].color = white_Color;
            SDL_RenderGeometry(renderer, nullptr, decorativeTriangleVertex, 3, nullptr, 0);
            // La palabra Squares
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
            SDL_FRect sq_s1{150, 130, 22, 5};
            SDL_RenderFillRect(renderer, &sq_s1);
            SDL_FRect sq_s2{150, 130, 6, 17}; 
            SDL_RenderFillRect(renderer, &sq_s2);
            SDL_FRect sq_s3{150, 142, 22, 5}; 
            SDL_RenderFillRect(renderer, &sq_s3);
            SDL_FRect sq_s4{166, 142, 6, 17};  
            SDL_RenderFillRect(renderer, &sq_s4);
            SDL_FRect sq_s5{150, 154, 22, 5}; 
            SDL_RenderFillRect(renderer, &sq_s5);

            SDL_FRect sq_q1{179, 130, 20, 5};   
            SDL_RenderFillRect(renderer, &sq_q1);
            SDL_FRect sq_q2{179, 130, 5, 29};  
            SDL_RenderFillRect(renderer, &sq_q2);
            SDL_FRect sq_q3{194, 130, 5, 29};  
            SDL_RenderFillRect(renderer, &sq_q3);
            SDL_FRect sq_q4{179, 154, 20, 5};  
            SDL_RenderFillRect(renderer, &sq_q4);
            SDL_FRect sq_q5{190, 149, 6, 10};  
            SDL_RenderFillRect(renderer, &sq_q5);

            SDL_FRect sq_u1{206, 130, 5, 24}; 
            SDL_RenderFillRect(renderer, &sq_u1);
            SDL_FRect sq_u2{221, 130, 5, 24};  
            SDL_RenderFillRect(renderer, &sq_u2);
            SDL_FRect sq_u3{206, 150, 20, 5}; 
            SDL_RenderFillRect(renderer, &sq_u3);

            SDL_FRect sq_a1{233, 132, 5, 27};   
            SDL_RenderFillRect(renderer, &sq_a1);
            SDL_FRect sq_a2{248, 132, 5, 27};   
            SDL_RenderFillRect(renderer, &sq_a2);
            SDL_FRect sq_a3{233, 130, 20, 5};   
            SDL_RenderFillRect(renderer, &sq_a3);
            SDL_FRect sq_a4{233, 142, 20, 4};   
            SDL_RenderFillRect(renderer, &sq_a4);

            SDL_FRect sq_r1{260, 130, 5, 27};   
            SDL_RenderFillRect(renderer, &sq_r1);
            SDL_FRect sq_r2{260, 130, 18, 5};  
            SDL_RenderFillRect(renderer, &sq_r2);
            SDL_FRect sq_r3{260, 141, 18, 5};   
            SDL_RenderFillRect(renderer, &sq_r3);
            SDL_FRect sq_r4{273, 134, 5, 8};    
            SDL_RenderFillRect(renderer, &sq_r4);
            SDL_FRect sq_r5{271, 144, 7, 13};  
            SDL_RenderFillRect(renderer, &sq_r5);

            SDL_FRect sq_e1{285, 130, 5, 27};   
            SDL_RenderFillRect(renderer, &sq_e1);
            SDL_FRect sq_e2{285, 130, 17, 5};  
            SDL_RenderFillRect(renderer, &sq_e2);
            SDL_FRect sq_e3{285, 141, 14, 5};   
            SDL_RenderFillRect(renderer, &sq_e3);
            SDL_FRect sq_e4{285, 152, 17, 5};  
            SDL_RenderFillRect(renderer, &sq_e4);

            SDL_FRect sq_s6{310, 130, 22, 5};  
            SDL_RenderFillRect(renderer, &sq_s6);
            SDL_FRect sq_s7{310, 130, 6, 17}; 
            SDL_RenderFillRect(renderer, &sq_s7);
            SDL_FRect sq_s8{310, 142, 22, 5}; 
            SDL_RenderFillRect(renderer, &sq_s8);
            SDL_FRect sq_s9{326, 142, 6, 17}; 
            SDL_RenderFillRect(renderer, &sq_s9);
            SDL_FRect sq_s10{310, 154, 22, 5}; 
            SDL_RenderFillRect(renderer, &sq_s10);

            // Palabra VS 
            SDL_FRect vs_v1{373, 181, 9, 23};   
            SDL_RenderFillRect(renderer, &vs_v1);
            SDL_FRect vs_v2{403, 181, 9, 23}; 
            SDL_RenderFillRect(renderer, &vs_v2);
            SDL_FRect vs_v3{380, 204, 9, 8};   
            SDL_RenderFillRect(renderer, &vs_v3);
            SDL_FRect vs_v4{396, 204, 9, 8};  
            SDL_RenderFillRect(renderer, &vs_v4);
            SDL_FRect vs_v5{387, 212, 11, 8}; 
            SDL_RenderFillRect(renderer, &vs_v5);

            SDL_FRect vs_s1{425, 181, 22, 5}; 
            SDL_RenderFillRect(renderer, &vs_s1);
            SDL_FRect vs_s2{425, 186, 6, 13};   
            SDL_RenderFillRect(renderer, &vs_s2);
            SDL_FRect vs_s3{425, 198, 22, 5};   
            SDL_RenderFillRect(renderer, &vs_s3);
            SDL_FRect vs_s4{441, 203, 6, 13};  
            SDL_RenderFillRect(renderer, &vs_s4);
            SDL_FRect vs_s5{425, 215, 22, 5};  
            SDL_RenderFillRect(renderer, &vs_s5);
            // Palabra Triangle
            SDL_FRect tri_t1{562, 230, 22, 5}; 
            SDL_RenderFillRect(renderer, &tri_t1);
            SDL_FRect tri_t2{569, 230, 8, 32};  
            SDL_RenderFillRect(renderer, &tri_t2);

            SDL_FRect tri_r1{594, 230, 7, 32}; 
            SDL_RenderFillRect(renderer, &tri_r1);
            SDL_FRect tri_r2{601, 230, 16, 6}; 
            SDL_RenderFillRect(renderer, &tri_r2);
            SDL_FRect tri_r3{601, 243, 16, 6}; 
            SDL_RenderFillRect(renderer, &tri_r3);
            SDL_FRect tri_r4{613, 235, 6, 9};   
            SDL_RenderFillRect(renderer, &tri_r4);
            SDL_FRect tri_r5{609, 246, 9, 16};  
            SDL_RenderFillRect(renderer, &tri_r5);

            SDL_FRect tri_i1{626, 230, 7, 32}; 
            SDL_RenderFillRect(renderer, &tri_i1);
            SDL_FRect tri_i2{621, 230, 17, 5};  
            SDL_RenderFillRect(renderer, &tri_i2);
            SDL_FRect tri_i3{621, 257, 17, 5};  
            SDL_RenderFillRect(renderer, &tri_i3);

            SDL_FRect tri_a1{649, 232, 6, 30};  
            SDL_RenderFillRect(renderer, &tri_a1);
            SDL_FRect tri_a2{668, 232, 6, 30};   
            SDL_RenderFillRect(renderer, &tri_a2);
            SDL_FRect tri_a3{649, 230, 25, 5};  
            SDL_RenderFillRect(renderer, &tri_a3);
            SDL_FRect tri_a4{649, 244, 25, 5};  
            SDL_RenderFillRect(renderer, &tri_a4);

            SDL_FRect tri_n1{681, 230, 7, 32};   
            SDL_RenderFillRect(renderer, &tri_n1);
            SDL_FRect tri_n2{701, 230, 7, 32};   
            SDL_RenderFillRect(renderer, &tri_n2);
            SDL_FRect tri_n3{688, 234, 8, 12};   
            SDL_RenderFillRect(renderer, &tri_n3);
            SDL_FRect tri_n4{693, 244, 8, 12};   
            SDL_RenderFillRect(renderer, &tri_n4);

            SDL_FRect tri_g1{715, 230, 7, 32};   
            SDL_RenderFillRect(renderer, &tri_g1);
            SDL_FRect tri_g2{715, 230, 22, 6};   
            SDL_RenderFillRect(renderer, &tri_g2);
            SDL_FRect tri_g3{715, 256, 22, 6}; 
            SDL_RenderFillRect(renderer, &tri_g3);
            SDL_FRect tri_g4{730, 243, 7, 19}; 
            SDL_RenderFillRect(renderer, &tri_g4);
            SDL_FRect tri_g5{724, 243, 13, 6}; 
            SDL_RenderFillRect(renderer, &tri_g5);

            SDL_FRect tri_l1{748, 230, 7, 32};  
            SDL_RenderFillRect(renderer, &tri_l1);
            SDL_FRect tri_l2{748, 257, 18, 5}; 
            SDL_RenderFillRect(renderer, &tri_l2);

            SDL_FRect tri_e1{777, 230, 7, 32}; 
            SDL_RenderFillRect(renderer, &tri_e1);
            SDL_FRect tri_e2{777, 230, 17, 5};  
            SDL_RenderFillRect(renderer, &tri_e2);
            SDL_FRect tri_e3{777, 243, 14, 5};  
            SDL_RenderFillRect(renderer, &tri_e3);
            SDL_FRect tri_e4{777, 257, 17, 5};  
            SDL_RenderFillRect(renderer, &tri_e4);

            //PALABRA START 
            SDL_FRect st_s1{300, 350, 22, 5};
            SDL_RenderFillRect(renderer, &st_s1);
            SDL_FRect st_s2{300, 350, 6, 17};
            SDL_RenderFillRect(renderer, &st_s2);
            SDL_FRect st_s3{300, 364, 22, 5};
            SDL_RenderFillRect(renderer, &st_s3);
            SDL_FRect st_s4{316, 364, 6, 17};
            SDL_RenderFillRect(renderer, &st_s4);
            SDL_FRect st_s5{300, 378, 22, 6};
            SDL_RenderFillRect(renderer, &st_s5);

            SDL_FRect st_t1{328, 350, 22, 5};
            SDL_RenderFillRect(renderer, &st_t1);
            SDL_FRect st_t2{335, 350, 8, 34};
            SDL_RenderFillRect(renderer, &st_t2);

            SDL_FRect st_a1{356, 352, 6, 32};
            SDL_RenderFillRect(renderer, &st_a1);
            SDL_FRect st_a2{375, 352, 6, 32};
            SDL_RenderFillRect(renderer, &st_a2);
            SDL_FRect st_a3{356, 350, 25, 5};
            SDL_RenderFillRect(renderer, &st_a3);
            SDL_FRect st_a4{356, 364, 25, 5};
            SDL_RenderFillRect(renderer, &st_a4);

            SDL_FRect st_r1{387, 350, 8, 34};
            SDL_RenderFillRect(renderer, &st_r1);
            SDL_FRect st_r2{396, 350, 19, 6};
            SDL_RenderFillRect(renderer, &st_r2);
            SDL_FRect st_r3{396, 364, 19, 6};
            SDL_RenderFillRect(renderer, &st_r3);
            SDL_FRect st_r4{408, 354, 7, 12};
            SDL_RenderFillRect(renderer, &st_r4);
            SDL_FRect st_r5{404, 368, 11, 16};
            SDL_RenderFillRect(renderer, &st_r5);

            SDL_FRect st_t3{421, 350, 22, 5};
            SDL_RenderFillRect(renderer, &st_t3);
            SDL_FRect st_t4{428, 350, 8, 34};
            SDL_RenderFillRect(renderer, &st_t4);
            // SEPARADOR 
            SDL_FRect sep_se{450, 353, 4, 28};
            SDL_RenderFillRect(renderer, &sep_se);
            // PALABRA ENTER 
            SDL_FRect ent_e1{466, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_e1);
            SDL_FRect ent_e2{475, 350, 21, 7};
            SDL_RenderFillRect(renderer, &ent_e2);
            SDL_FRect ent_e3{475, 364, 17, 6};
            SDL_RenderFillRect(renderer, &ent_e3);
            SDL_FRect ent_e4{475, 378, 21, 6};
            SDL_RenderFillRect(renderer, &ent_e4);

            SDL_FRect ent_n1{502, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_n1);
            SDL_FRect ent_n2{530, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_n2);
            SDL_FRect ent_n3{510, 354, 10, 10};
            SDL_RenderFillRect(renderer, &ent_n3);
            SDL_FRect ent_n4{520, 366, 10, 10};
            SDL_RenderFillRect(renderer, &ent_n4);

            SDL_FRect ent_t1{545, 350, 23, 7};
            SDL_RenderFillRect(renderer, &ent_t1);
            SDL_FRect ent_t2{552, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_t2);

            SDL_FRect ent_e5{574, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_e5);
            SDL_FRect ent_e6{583, 350, 21, 7};
            SDL_RenderFillRect(renderer, &ent_e6);
            SDL_FRect ent_e7{583, 364, 17, 6};
            SDL_RenderFillRect(renderer, &ent_e7);
            SDL_FRect ent_e8{583, 378, 21, 6};
            SDL_RenderFillRect(renderer, &ent_e8);

            SDL_FRect ent_r1{611, 350, 9, 34};
            SDL_RenderFillRect(renderer, &ent_r1);
            SDL_FRect ent_r2{620, 350, 21, 7};
            SDL_RenderFillRect(renderer, &ent_r2);
            SDL_FRect ent_r3{620, 364, 21, 7};
            SDL_RenderFillRect(renderer, &ent_r3);
            SDL_FRect ent_r4{636, 355, 8, 12};
            SDL_RenderFillRect(renderer, &ent_r4);
            SDL_FRect ent_r5{631, 368, 13, 16};
            SDL_RenderFillRect(renderer, &ent_r5);
    }

   void TitleScene::HandleEvent(const SDL_Event &event){
        if (event.type == SDL_EVENT_KEY_DOWN)
            if (event.key.key == SDLK_SPACE || event.key.key == SDLK_RETURN)
                m_manager->ChangeScene(std::make_unique<GameScene>(m_manager, "GameScene"));
    }
