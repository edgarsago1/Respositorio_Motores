#include "../../../include/Engine/Components/AnimationComponent.hpp"

#include "../../../include/Engine/Components/SpriteComponent.hpp"
#include "../../../include/Engine/GameObject.hpp" 

    void AnimationComponent::Init(){
        if(!owner) return;
        SpriteComponent *sprite = owner->GetComponent<SpriteComponent>();
        if(sprite){
            m_sprite = sprite;
            UpdateSrcRect();
        }
    }
    void AnimationComponent::AddClip(const std::string &name, int row, int totalFrames, float frameDuration, bool loop, int startFrame){
        AnimationClip new_clip{name, row, startFrame, totalFrames, frameDuration, loop};
        auto [it, inserted] = m_clips.emplace(name, new_clip);
        // Reproducir la primera animación registrada.
        if (inserted && m_clips.size() == 1)
            Play(name);
    }

    bool AnimationComponent::Play(const std::string &name){
        auto it = m_clips.find(name);
        if (it == m_clips.end())
            return false; // No existe la animación
        if (m_currentClip == name && m_isPlaying)
            return true;
        m_currentClip = name;
        m_currentFrameIndex = 0;
        m_elapsedTime = 0.0f;
        m_isPlaying = true;
        UpdateSrcRect();
        return true;

    }

    void AnimationComponent::Update(float dt){
        if (!m_isPlaying || m_currentClip.empty())
            return;
        auto it = m_clips.find(m_currentClip);
        if (it == m_clips.end())
            return;
        const AnimationClip& clip = it->second;
        m_elapsedTime += dt;
        bool frameChanged = false;
        while (m_elapsedTime >= clip.frameDuration) {
            m_elapsedTime -= clip.frameDuration;
            ++m_currentFrameIndex;
            frameChanged = true;
            if (m_currentFrameIndex >= clip.totalFrames) {
                if (clip.loop) {
                    m_currentFrameIndex = 0;
                } else {
                    // Congelar el último fotograma.
                    m_currentFrameIndex = clip.totalFrames - 1;
                    m_isPlaying = false;
                    m_elapsedTime = 0.0f;
                    break;
                }
            }
        }
        if (frameChanged)
            UpdateSrcRect();
    }

    void AnimationComponent::UpdateSrcRect(){
        if(m_currentClip.empty() || !m_sprite) return;
        auto it = m_clips.find(m_currentClip);
        if (it == m_clips.end())
        return;
        const AnimationClip& clip = it->second;
        int col = clip.startFrame + m_currentFrameIndex;
        int sep_x = separation_x * col;
        int sep_y =  separation_y * clip.row;
        SDL_FRect rect{
            pos_x + col * (m_frameWidth + separation_x)  ,
            pos_y + clip.row * (m_frameHeight + separation_y),
            m_frameWidth,
            m_frameHeight
        };
        m_sprite->SetSourceRect(rect);
    }

