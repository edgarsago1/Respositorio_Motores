#pragma once
#include "../../Engine/Component.hpp"
#include <memory>
#include <SDL3/SDL.h>

class SpriteComponent : public Component{
private:
    SDL_Texture* m_texture{nullptr};
    bool m_useSrcRect{false};
    SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
    float m_width{0.0f};
    float m_height{0.0f};
    SDL_Color m_colorMod{255, 255, 255, 255};
    SDL_FlipMode m_flip{SDL_FLIP_NONE};
public:
    SpriteComponent() = default;

    // Damos un constructor con configuraciones opcionales: Recibe siempre la textura y el tamaño que ocupara en pantalla (width, height)
    // OPCIONAL IMPLEMENTADO: srcRect permite extraer un fragmento de la imagen y desplegar solo ese fragmento en pantalla (Los assets son generalmente planos con muchos diseños/perspectivas
    // es mejor tener todo en una misma imagen y recortar solo que usas que tener muchos archivos para cargar)
    // OPCIONAL IMPLEMENTADO: colorMod permite aplicar un tinte sobre la misma textura para un objeto/componente sin afectar a los demás
    // OPCIONAL NO IMPLEMENTADO: flip, permite desplegar la textura en distintas posiciones y orientaciones, de momento no funciona, es necesario permitir set de rotación y otros movimientos
    explicit SpriteComponent(SDL_Texture* texture, float width, float height, SDL_FRect srcRect = {0.0f, 0.0f, 0.0f, 0.0f}, SDL_Color colorMod = {255, 255, 255, 255}, SDL_FlipMode flip = SDL_FLIP_NONE)
        : m_texture(texture), m_width(width), m_height(height), m_srcRect(srcRect), m_colorMod(colorMod), m_flip(flip) {
        if (srcRect.w > 0.0f && srcRect.h > 0.0f)
            m_useSrcRect = true;
    }
    void Render(SDL_Renderer *renderer) override;
};