#include "../Engine/Scene.hpp"

#include "../Physics/CollisionManager.hpp"
#include "../Engine/ResourceManager.hpp"

class ResourceDemoScene : public Scene{
    private:
        CollisionManager m_collisionManager;
        
        std::vector<std::unique_ptr<GameObject>> m_pendingObjects; // Creamos un vector que guarde los objetos a añadir en la escena
        using Scene::Scene;
        float m_physicsAccumulator{0.0f};
        bool m_debugDraw{false};

        float pos_x{50.0f};

        float pos_y{30.0f};
        
    public: 
        void Init() override;
        // Fase de Actualización: La misma que solíamos tener en main
        void Update(float dt) override;

        void Render(SDL_Renderer *renderer) override;

        virtual void HandleEvent(const SDL_Event &event) override;

        // Para añadir nuevos objetos, seguimos una filosofía similar, creamos un vector con los objetos que queremos insertar en la escena y al final de todos los procesos se añaden de manera segura
        void ProcessPendingObjects();

        // Añade los objetos a la lista de objetos pendientes.
        void Spawn(std::unique_ptr<GameObject> object) override;
};