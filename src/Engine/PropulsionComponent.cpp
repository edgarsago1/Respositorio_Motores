#include "../../include/Engine/PropulsionComponent.hpp"

#include "../../include/Engine/GameObject.hpp"


void PropulsionComponent::FixedUpdate(float fixed_dt){
    traveled_distance += timer_speed * fixed_dt;
    for(int i = 0; i < number_particles; i++){
        particles_pos[i] = particles_pos[i] + particles_dir[i] * particles_speed[i] * fixed_dt;
    }
    if(traveled_distance > 1.0f){
        owner->Destroy();
    }
}

void PropulsionComponent::Render(SDL_Renderer *renderer){
    if(!is_dead){
        for(int i = 0; i < number_particles; i++){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_FRect particle{ particles_pos[i].x, particles_pos[i].y, size, size};
            SDL_RenderFillRect(renderer, &particle);
        }
    }
}