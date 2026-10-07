#pragma once
#include "Component.hpp"
#include "../Math/Vector2.hpp"

class AsteroidComponent : public Component{
    private:
        int stage{2};
        Vector2 size{80.0f, 80.0f};
        Vector2 direction{1.0, 0.0f};
        float speed{100.0f};
    public:
        AsteroidComponent(int stg, Vector2 sz, Vector2 dir, float spd) : stage(stg), size(sz), direction(dir), speed(spd) {}
        
        //Simplemente hace que el Asteroide deambule por el territorio
        void FixedUpdate(float fixed_dt) override;

        // Hace una revisión de colisión solo si fue contra un proyectil, crea dos asteroides hijos dependiendo de su stage (stage == 0 implica 0 hijos) y destruye el asteroide actual.
        //  Los hijos son la mitad de pequeños y un 30% más rápidos.
        void OnCollision(GameObject *other) override;

        int getStage() const;
};