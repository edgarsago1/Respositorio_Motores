#include "../../include/Engine/ShipControllerComponent.hpp"

#include <cmath>
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TriangleRenderComponent.hpp"

void ShipControllerComponent::FixedUpdate(float fixed_dt){

    if (!owner) return;
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
        if (!transform) return;
        // Lectura continua de teclado
        left_click_pressed = false;
        const bool *keys = SDL_GetKeyboardState(nullptr);
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(nullptr, nullptr);

        if (keys[SDL_SCANCODE_1]) follow_mouse = !follow_mouse; // Por el momento haremos que 1 alterne el modo de movimiento}
        if (!follow_mouse){
            float current_angular_speed = 0.0f;
            if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
                current_angular_speed -= angular_speed;
            }
            if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
                current_angular_speed += angular_speed;
            }
            if (current_angular_speed != 0.0f) {
                transform->Rotate(current_angular_speed, &orientation);
                transform->Rotate(current_angular_speed, &trianglevertex[0]);
                transform->Rotate(current_angular_speed, &trianglevertex[1]);
                } 
        } else {
            Vector2 mouse_pos;
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            Vector2 mouse_dir = mouse_pos - transform->position;
            mouse_dir = mouse_dir.normalized(); // Puede quitarse o no dependiendo de las pruebas
            float walk_angle = static_cast<float>(std::atan2(mouse_dir.y, mouse_dir.x));
            orientation.x = std::cos(walk_angle);
            orientation.y = std::sin(walk_angle);
            orientation = orientation.normalized();
            Vector2 perpendicular{
                -orientation.y,
                orientation.x
            };
            Vector2 baseCenter = orientation * 0.0f; // Ajusta la posición de la base del triángulo según sea necesario
            trianglevertex[0] = baseCenter + perpendicular * 0.5f;
            trianglevertex[1] = baseCenter - perpendicular * 0.5f;
        }
        if(buttons & SDL_BUTTON_LMASK) left_click_pressed = true;        
        Vector2 final_direction = {0, 0};
        if(!follow_mouse){
            if(keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
                final_direction = orientation;
        } else {
            if(left_click_pressed)
                final_direction = orientation;
        }
        Vector2 displacement = final_direction * (speed * fixed_dt);
        transform->Translate(displacement);
        // 5. Mantener dentro de la ventana (960 x 540)
        Vector2 max_bounds{960.0f, 540.0f};
        if (auto *rect = owner->GetComponent<TriangleRenderComponent>())
            max_bounds = max_bounds - (rect->size * transform->scale.x);
        transform->position = transform->position.clamp(Vector2{0.0f, 0.0f}, max_bounds);
        
}

Vector2 ShipControllerComponent::getOrientation(){
    return orientation;
}

std::vector<Vector2> ShipControllerComponent::getTriangleVertex(){
    return trianglevertex;
}