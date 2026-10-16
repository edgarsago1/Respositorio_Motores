#include "../../include/Engine/ResourceManager.hpp"

// Limpieza de cache, eliminación de punteros y entradas dentro de nuestro mapeo de texturas
void ResourceManager::Clear() {
    m_textures.clear();
}