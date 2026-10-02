#pragma once

#include <SDL3/SDL.h>

// Declaración anticipada (Forward Declaration)
class GameObject;

class Component
{
public:
// Puntero de vuelta al padre
GameObject *owner{nullptr};
virtual void OnCollision(GameObject *other){}
// Destructor virtual
virtual ~Component() = default;

// Métodos virtuales del ciclo de vida
virtual void Init() {}

// Actualización por fotograma de renderizado.
virtual void Update(float dt) {}

// Actualización de física a paso de tiempo fijo
virtual void FixedUpdate(float fixed_dt){}

virtual void Render(SDL_Renderer *renderer) {}
};