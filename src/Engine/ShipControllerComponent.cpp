#include "../../include/Engine/ShipControllerComponent.hpp"

#include <cmath>
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/Scene.hpp"
#include "../../include/Engine/TriangleRenderComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Engine/ProjectileComponent.hpp"
#include "../../include/Engine/AsteroidComponent.hpp"
#include "../../include/Engine/ExplosionComponent.hpp"
#include "../../include/Physics/ColliderComponent.hpp"
#include "../../include/Game/GameScene.hpp"
void ShipControllerComponent::FixedUpdate(float fixed_dt){

    if (!owner) return;
        TransformComponent *transform = owner->GetComponent<TransformComponent>();
        if (!transform) return;
        // Lectura continua de teclado
        left_click_pressed = false;
        const bool *keys = SDL_GetKeyboardState(nullptr);
        bool advance_mouse_control = false;
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(nullptr, nullptr);
        // Modo control tanque
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
        } else { // Modo Mouse
            Vector2 mouse_pos;
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            Vector2 mouse_dir = mouse_pos - transform->position;
            if (mouse_dir.length() >= 25.0f){
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
            advance_mouse_control = true;
            }
        }
        if(buttons & SDL_BUTTON_LMASK) left_click_pressed = true;        
        Vector2 final_direction = {0, 0};
        if(!follow_mouse){ // Lo anterior era la forma de orientar la nave, esta es la forma de hacerlo avanzar de acuerdo a su vector de dirección
            if(keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
                final_direction = orientation;
        } else {
            if(left_click_pressed && advance_mouse_control)
                final_direction = orientation;
        }

        current_cooldown--; // llevamos la cuenta de fotogramas para marcar el cooldown de proyectiles
        // Creación del objeto proyectiles 
        if(((buttons & SDL_BUTTON_RMASK) || keys[SDL_SCANCODE_RETURN] ) && current_cooldown <= 0 && current_invincibleFrame <= 0){
            current_cooldown = shoot_cooldown;
            auto projectile = std::make_unique<GameObject>("Projectile");
            projectile->AddComponent<TransformComponent>(transform->position + orientation * 30.0f, Vector2{1.0f, 1.0f});
            projectile->AddComponent<RectRenderComponent>(Vector2{5.0f, 5.0f}, SDL_Color{255, 255, 255, 255});
            projectile->AddComponent<ProjectileComponent>(speed*2, Vector2{5.0f, 5.0f}, orientation, 400.0f);
            projectile->AddComponent<ColliderComponent>(Vector2{5.0f, 5.0f});
            owner->GetScene()->Spawn(std::move(projectile));
        }    
        Vector2 displacement = final_direction * (speed * fixed_dt);
        transform->Translate(displacement);
        // Mantener dentro de la ventana (960 x 540)
        Vector2 max_bounds{960.0f, 540.0f};
        Vector2 size_triangle{0, 0};
        transform->teleportObject(max_bounds, {0.0f, 0.0f});
        auto* triangle = owner->GetComponent<TriangleRenderComponent>();
        if (triangle)
        {
            triangle->setShow(current_deathCooldown <= 0); // Lo hace visible solo si no está en periodo de muerte
            triangle->setTransparent(current_invincibleFrame >= 0); // Lo hace transparente si está en periodo de invencibilidad
        }
        current_deathCooldown--;
        current_invincibleFrame--;
}

void ShipControllerComponent::OnCollision(GameObject *other){
    if(!owner) return;
    AsteroidComponent *asteroid_other = other->GetComponent<AsteroidComponent>();
    if(!asteroid_other) return;
    if(current_invincibleFrame <= 0 ){
        InvincibilityPeriod();
        if(auto *scene = dynamic_cast<GameScene*>(owner->GetScene())) //Ahora el manejo de vidas lo lleva el manager
            scene->GetRoundManager()->LostLife();
        if(auto *transform = owner->GetComponent<TransformComponent>()){
            auto explosion = std::make_unique<GameObject>("Explosion");
            explosion->AddComponent<ExplosionComponent>(transform->position, 8);
            owner->GetScene()->Spawn(std::move(explosion));
        }
    }

}

void ShipControllerComponent::InvincibilityPeriod(){
    current_deathCooldown = death_cooldown;
    current_invincibleFrame = invincible_frames;
}

void ShipControllerComponent::changeControllers(){
    follow_mouse = !follow_mouse;
}

Vector2 ShipControllerComponent::getOrientation(){
    return orientation;
}

std::vector<Vector2> ShipControllerComponent::getTriangleVertex(){
    return trianglevertex;
}

