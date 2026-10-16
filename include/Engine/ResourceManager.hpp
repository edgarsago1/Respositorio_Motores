#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct TextureDeleter{
    void operator()(SDL_Texture *texture) const noexcept{
    if (texture) 
        SDL_DestroyTexture(texture);
    }
};

using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class ResourceManager{
private:
    SDL_Renderer *m_renderer{nullptr};
    std::unordered_map<std::string, TexturePtr> m_textures;
public:
    ResourceManager() = default;
    explicit ResourceManager(SDL_Renderer *renderer);
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;
    ResourceManager(ResourceManager &&) noexcept = default;
    ResourceManager &operator=(ResourceManager &&) noexcept = default;
    void SetRenderer(SDL_Renderer *renderer) { m_renderer = renderer; }
    SDL_Renderer *GetRenderer() const { return m_renderer; }

    SDL_Texture *GetTexture(const std :: string &filepath){
        for(const auto& [name, texture] : m_textures){
            if (name == filepath)
                return texture.get();
        }
        if(!m_renderer) return nullptr;
        SDL_Surface* surface = IMG_Load(filepath.c_str());
        if (!surface){
            SDL_Log("ERROR IMG_Load: %s", SDL_GetError());
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (!texture){
            SDL_Log("ERROR CreateTextureFromSurface: %s", SDL_GetError());
            return nullptr;
        }
        SDL_DestroySurface(surface);
        TexturePtr texturePtr(texture);
        auto [it, inserted] = m_textures.emplace(filepath, std::move(texturePtr));
        SDL_Log("Nueva textura ÚNICA agregada");
        return it->second.get();
    }

    bool HasTexture(const std :: string &filepath) const;
    size_t GetTextureCount() const { return m_textures.size(); }
    bool UnloadTexture(const std :: string &filepath);
    void Clear();
};