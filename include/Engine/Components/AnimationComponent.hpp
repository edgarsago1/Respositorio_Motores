#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <SDL3/SDL.h>
#include "../Component.hpp"
#include "../../Math/Vector2.hpp"

struct AnimationClip{
    std::string name;
    int row{0}; // Fila en la hoja de sprites
    int startFrame{0}; // Columna inicial
    int totalFrames{1}; // Cantidad de cuadros en la secuencia
    float frameDuration{0.1f}; // Duración en segundos de cada cuadro
    bool loop{true}; // Si la animación se repite indefinidamente
};

class SpriteComponent;

class AnimationComponent : public Component{
private:
    SpriteComponent *m_sprite{nullptr};
    int pos_x = 0;
    int pos_y = 0;
    int separation_x = 0;
    int separation_y = 0;
    int m_frameWidth{32};
    int m_frameHeight{32};
    std::unordered_map<std::string, AnimationClip> m_clips;
    std::string m_currentClip;
    int m_currentFrameIndex{0};
    float m_elapsedTime{0.0f};
    bool m_isPlaying{true};
    void UpdateSrcRect();
public:
    AnimationComponent() = default;
    AnimationComponent(int frameWidth = 32, int frameHeight = 32, int px = 0, int py = 0, int sx = 0, int sy = 0): 
        m_frameWidth{frameWidth}, 
        m_frameHeight{frameHeight},
        pos_x{px}, // Posición de inicio del primer sprite en la spritesheet
        pos_y{py},
        separation_x{sx},   // Píxeles de separación entre sprite dentro de la spritesheet 
        separation_y{sy} {

    }
    ~AnimationComponent() override = default;
    void SetFrameDimensions(int width, int height);
    void AddClip(const std::string &name, int row, int totalFrames, float frameDuration = 0.1f, bool loop = true, int startFrame = 0);
    bool Play(const std::string &name);
    void Stop();
    void Resume();
    const std::string &GetCurrentClip() const { return m_currentClip; }
    int GetCurrentFrameIndex() const { return m_currentFrameIndex; }
    bool IsPlaying() const { return m_isPlaying; }
    void Init() override;
    void Update(float dt) override;

};