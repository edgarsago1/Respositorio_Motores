#include "../../../Include/Engine/Components/PlayerControllerComponent.hpp"    
    
#include "../../../Include/Engine/Components/AnimationComponent.hpp"
#include "../../../Include/Engine/Components/SpriteComponent.hpp"
    void PlayerControllerComponent::FixedUpdate(float fixed_dt){
            if (!owner) return;
            TransformComponent *transform = owner->GetComponent<TransformComponent>();
            if (!transform) return;

            // 1. Lectura continua de teclado
            const bool *keys = SDL_GetKeyboardState(nullptr);
            Vector2 input_dir{0.0f, 0.0f};
            if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) input_dir.x -= 1.0f;
            if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) input_dir.x += 1.0f;
            Vector2 final_dir = input_dir;
            // 2. Persecución del cursor del mouse

            // 3. Normalización del vector resultante
            if (final_dir.length_squared() > 0.01f)
            {   
                if(auto animation = owner->GetComponent<AnimationComponent>()){

                    if(auto sprite = owner->GetComponent<SpriteComponent>())
                        if(0 > final_dir.x ){
                            sprite->SetFlipMode(SDL_FLIP_HORIZONTAL);

                        } else if (final_dir.x > 0 ) {
                            sprite->SetFlipMode(SDL_FLIP_NONE);
                        }
                        
                    animation->Play("Walk");
                }
                final_dir = final_dir.normalized();
            } else {
                final_dir = {0.0f, 0.0f};
                if(auto animation = owner->GetComponent<AnimationComponent>())
                    animation->Play("Idle");
            }
            
            // 4. Traslación del transform
            Vector2 displacement = final_dir * (speed * fixed_dt);
            transform->Translate(displacement);
            // 5. Mantener dentro del mundo 
            Vector2 max_bounds{2400.0f, 540.0f};
            if (auto *rect = owner->GetComponent<RectRenderComponent>())
            {
                max_bounds = max_bounds - (rect->size * transform->scale.x);
            }
            transform->position = transform->position.clamp(Vector2{0.0f, 0.0f}, max_bounds);
        }