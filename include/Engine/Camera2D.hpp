#pragma once
#include <SDL3/SDL.h>
#include "../Math/Vector2.hpp"
class Camera2D
{
private:
static Camera2D *s_mainCamera;

Vector2 m_position{0.0f, 0.0f}; // Coordenada superior-izquierda en espacio de mundo

Vector2 m_viewportSize{960.0f, 540.0f}; // Dimensiones en píxeles del área visible en pantalla
bool m_useBounds{false};
Vector2 m_minBounds{0.0f, 0.0f};
Vector2 m_maxBounds{0.0f, 0.0f};

bool m_followHorizontal{true};
bool m_followVertical{true};
public:
Camera2D(){
    if(s_mainCamera == nullptr)
        s_mainCamera = this;
}
Camera2D(float viewportW, float viewportH){
    if(s_mainCamera == nullptr)
        s_mainCamera = this;
    m_viewportSize = Vector2{viewportW, viewportH};    
}
~Camera2D(){
    if(s_mainCamera == this)
        s_mainCamera = nullptr;
}

static Camera2D *GetMain() { return s_mainCamera; }
static void SetMain(Camera2D *camera) { s_mainCamera = camera; }
void SetPosition(const Vector2 &pos);
const Vector2 &GetPosition() const { return m_position; }
void SetViewportSize(float w, float h) { m_viewportSize = Vector2{w, h};
}
const Vector2 &GetViewportSize() const { return m_viewportSize; }
void SetBounds(const Vector2 &minBounds, const Vector2 &maxBounds);
void ClearBounds() { m_useBounds = false; }
bool HasBounds() const { return m_useBounds; }
void SetFollowHorizontal(bool enabled){ m_followHorizontal = enabled;}
void SetFollowVertical(bool enabled){ m_followVertical = enabled;}
// Centra la vista en una coordenada de mundo específica
void CenterOn(const Vector2 &targetPos);
// Seguimiento suave del objetivo mediante interpolación lineal (Lerp)
void Follow(const Vector2 &targetPos, float smoothSpeed, float dt);
// Transformación de coordenadas
Vector2 WorldToScreen(const Vector2 &worldPos) const;
Vector2 ScreenToWorld(const Vector2 &screenPos) const;
// Descarte de renderizado para entidades fuera del visor (Frustum Culling)
bool IsVisible(const SDL_FRect &worldRect) const;
// Aplica la transformación de vista considerando el factor de desplazamiento en paralaje
SDL_FRect ApplyToRect(const SDL_FRect &worldRect, const Vector2&parallaxFactor = Vector2{1.0f, 1.0f}) const;
};