#pragma once
#include <vector>
#include <random>
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "../Math/Vector2.hpp"
class ExplosionComponent: public Component{
    private:
        int number_particles{8};
        std::vector<Vector2> particles_pos;
        std::vector<Vector2> particles_dir;
        float traveled_distance{0.0f};
        float speed{50.0f};
        float size{1.5f};
    public:
        // Al crearse una explosión, se crean una serie de partículas y se les asigna una dirección aleatoria, todos parten desde el origen de la explosión
        ExplosionComponent(Vector2 position, int particles) : number_particles{particles} {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
            for(int i = 0; i < number_particles; i++){
                particles_pos.push_back(position);
                particles_dir.push_back(Vector2{distribution(generator), distribution(generator)}.normalized());
            } 
        }
        // Simplemente las partículas siguen sus direcciones a una velocidad fija para luego destruir el objeto
        void FixedUpdate(float fixed_dt) override;
        
        // Dibuja cada una de las partículas.
        void Render(SDL_Renderer *renderer) override;
};
