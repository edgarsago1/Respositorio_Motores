#include "../../include/Engine/Camera2D.hpp"

#include <algorithm> // for std::clamp
Camera2D* Camera2D::s_mainCamera = nullptr;
void Camera2D::SetPosition(const Vector2 &pos){
    m_position = pos;
    if(m_useBounds){
        m_position.x = std::clamp(m_position.x, m_minBounds.x, m_maxBounds.x);
        m_position.y = std::clamp(m_position.y, m_minBounds.y, m_maxBounds.y);

    }
}

void Camera2D::SetBounds(const Vector2 &minBounds, const Vector2 &maxBounds){
    m_minBounds = minBounds;
    m_maxBounds = maxBounds;
}
void Camera2D::CenterOn(const Vector2 &targetPos){
    SetPosition(targetPos -m_viewportSize * 0.5f);
}

void Camera2D::Follow(const Vector2 &targetPos, float smoothSpeed, float dt){
    Vector2 desiredPos = Vector2{};
    if(m_followHorizontal) 
        desiredPos.x = targetPos.x - m_viewportSize.x * 0.5f;
    if(m_followVertical) 
        desiredPos.y = targetPos.y - m_viewportSize.y * 0.5f;
    SetPosition(m_position.Lerp(desiredPos, std::clamp(smoothSpeed * dt, 0.0f, 1.0f)));
}

SDL_FRect Camera2D::ApplyToRect(const SDL_FRect &worldRect, const Vector2&parallaxFactor) const{
    SDL_FRect rect{
            worldRect.x - (m_position.x *parallaxFactor.x),
            worldRect.y - (m_position.y *parallaxFactor.y),
            worldRect.w,
            worldRect.h
        };
    return rect;
}

bool Camera2D::IsVisible(const SDL_FRect &worldRect) const{
    SDL_FRect a{
            0,
            0,
            m_viewportSize.x,
            m_viewportSize.y
        };
    return (a.x < (worldRect.x + worldRect.w)) && ((a.x + a.w) > worldRect.x) && (a.y < (worldRect.y +worldRect.h)) && ((a.y + a.h) > worldRect.y);
}