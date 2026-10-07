#include "../../include/Engine/ExplosionComponent.hpp"

#include "../../include/Engine/GameObject.hpp"


void ExplosionComponent::FixedUpdate(float fixed_dt){
    traveled_distance += speed * fixed_dt;
    for(int i = 0; i < number_particles; i++){
        particles_pos[i] = particles_pos[i] + particles_dir[i] * speed * fixed_dt;
    }
    if(traveled_distance > 30.0f){
        owner->Destroy();
    }
}

void ExplosionComponent::Render(SDL_Renderer *renderer){
    for(int i = 0; i < number_particles; i++){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_FRect particle{ particles_pos[i].x, particles_pos[i].y, size, size};
        SDL_RenderFillRect(renderer, &particle);
    }
}