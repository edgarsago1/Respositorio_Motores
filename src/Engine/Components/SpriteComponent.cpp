#include "../../../include/Engine/Components/SpriteComponent.hpp"

#include "../../../include/Engine/Components/TransformComponent.hpp"
#include "../../../include/Engine/GameObject.hpp"
#include "../../../include/Engine/Camera2D.hpp"

void SpriteComponent::Render(SDL_Renderer *renderer){
    if (!renderer || !m_texture) return;
    SDL_FRect dstRect{0.0f, 0.0f, m_width, m_height};
    double rotation = 0.0;
    if (owner){
        auto *transform = owner->GetComponent<TransformComponent>();
        if (transform){
            dstRect.x = transform->position.x;
            dstRect.y = transform->position.y;
            dstRect.w =  m_width * transform->scale.x;
            dstRect.h = m_height * transform->scale.y;
        }
        if(m_affectedByCamera){
            auto *camera = Camera2D::GetMain();
            if(camera){
                dstRect = camera->ApplyToRect(dstRect, m_parallaxFactor);
                if(!camera->IsVisible(dstRect))
                   return;
    
            }
        }
    }
    // Aplicar modulación de color y alfa al recurso compartido (Flyweight)
    SDL_SetTextureColorModFloat(
    m_texture,
    m_colorMod.r / 255.0f,
    m_colorMod.g / 255.0f,
    m_colorMod.b / 255.0f
    );

    SDL_SetTextureAlphaModFloat(
    m_texture,
    m_colorMod.a / 255.0f
    );

    const SDL_FRect *src = m_useSrcRect ? &m_srcRect : nullptr;
    SDL_RenderTextureRotated(renderer, m_texture, src, &dstRect, rotation,
    nullptr, m_flip);

    // Restaurar modulación por defecto para no contaminar a otros sprites
    SDL_SetTextureColorModFloat(m_texture, 1.0f, 1.0f, 1.0f);
    SDL_SetTextureAlphaModFloat(m_texture, 1.0f);
}

void SpriteComponent::SetSourceRect(SDL_FRect rect){
    m_useSrcRect = true;
    m_srcRect = rect;
}