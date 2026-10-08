#pragma once

#include <vector>
#include <random>
#include "Component.hpp"
#include "../Math/Vector2.hpp"

class PropulsionComponent : public Component{
    private:
        Vector2 position;
        int number_particles{8};
        std::vector<Vector2> particles_pos; // Posición de inicio de las partículas
        std::vector<Vector2> particles_dir; // Dirección de cada una de las partículas aleatorias
        std::vector<float> particles_speed; // Velocidad aleatoria para cada partícula
        bool is_dead = false; // Damos seguimiento si ship se ha desvanecido temporalmente o no.
        float traveled_distance{0.0f};
        float timer_speed{50.0f}; // La velocidad en este caso actúa como un temporizador para borrar el trazo de partículas
        float size{2.0f};
    public:

        // Creamos las partículas desde el lugar de avance del ship dándole una dirección aleatoria que generalmente será contraria a la dirección del ship
        PropulsionComponent(Vector2 pos, Vector2 ship_direction, float speed, int particles, int death_cooldown): position{pos}, timer_speed{speed}, number_particles{particles}{
            Vector2 direction = Vector2{-ship_direction.x, -ship_direction.y};
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_real_distribution<float> angle_distribution(-180.0f, 180.0f);
            std::uniform_real_distribution<float> speed_distribution(10.0f, 50.0f);
            for(int i = 0; i < number_particles ; i++){
                particles_pos.push_back(position);
                particles_dir.push_back(direction.Rotated(angle_distribution(generator)));
                particles_speed.push_back(speed_distribution(generator)); // Les damos una velocidad aleatoria
            }
            is_dead = (0 < death_cooldown);
        }

        void FixedUpdate(float fixed_dt) override;

        // Las partículas solo se muestra si el player no está en cooldown de muerte
        void Render(SDL_Renderer *renderer) override;
};