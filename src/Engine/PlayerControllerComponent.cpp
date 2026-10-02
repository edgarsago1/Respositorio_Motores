#include "../../include/Engine/PlayerControllerComponent.hpp"

#include <SDL3/SDL.h>
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Math/Vector2.hpp"

void PlayerControllerComponent::FixedUpdate(float fixed_dt){
        if (!owner) return;
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
        if (!transform) return;
        // 1. Lectura continua de teclado
        const bool *keys = SDL_GetKeyboardState(nullptr);
        Vector2 input_dir{0.0f, 0.0f};
        if (keys[SDL_SCANCODE_1]) follow_mouse = !follow_mouse;
        if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) input_dir.y -= 1.0f;
        if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) input_dir.y += 1.0f;
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) input_dir.x -= 1.0f;
        if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) input_dir.x += 1.0f;
        Vector2 final_dir = input_dir;
        // 2. Persecución del cursor del mouse
        if (follow_mouse){
            Vector2 mouse_pos;
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            Vector2 center_offset{30.0f, 30.0f};
            if (auto *rect = owner->GetComponent<RectRenderComponent>())
                center_offset = (rect->size * transform->scale.x) * 0.5f;
            Vector2 mouse_dir = mouse_pos - (transform->position + center_offset);
            if (mouse_dir.length() >= 50.0f)
                final_dir = input_dir + mouse_dir.normalized();
        }
        // 3. Normalización del vector resultante
        if (final_dir.length_squared() > 0.01f)
        {
            final_dir = final_dir.normalized();
        } else {
            final_dir = {0.0f, 0.0f};
        }

        // 4. Traslación del transform
        Vector2 displacement = final_dir * (speed * fixed_dt);
        transform->Translate(displacement);
        // 5. Mantener dentro de la ventana (960 x 540)
        Vector2 max_bounds{960.0f, 540.0f};
        if (auto *rect = owner->GetComponent<RectRenderComponent>())
            max_bounds = max_bounds - (rect->size * transform->scale.x);
        transform->position = transform->position.clamp(Vector2{0.0f, 0.0f}, max_bounds);
   }