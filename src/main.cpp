#define SDL_MAIN_USE_CALLBACKS 1

// Bibliotecas externas
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Importación de clases
#include "Vector2.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "PatrolComponent.hpp"
#include "CollisionManager.hpp"
#include "BallComponent.hpp"

void SDL_LogPlatformInfo(); 



struct AppState
{
    SDL_Renderer *renderer{nullptr};
    SDL_Window *window{nullptr};

    // Temporizador para Delta Time
    Uint64 last_ticks{0};
    float physics_accumulator{0.0f};
    // Modo de depuración visual para inspeccionar colisionadores
    bool debug_draw{true};
    // Todas las entidades
    std::vector<std::unique_ptr<GameObject>> entities;
    CollisionManager collisionManager{&entities};

} appstate;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al inicializar SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Sugerir a la plataforma una tasa objetivo de 60 FPS
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");

    SDL_LogPlatformInfo();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Práctica 02 - Vectores y Movimiento", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al crear ventana o renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

    ::appstate.window = window;
    ::appstate.renderer = renderer;
    ::appstate.last_ticks = SDL_GetTicks();

    *appstate = &::appstate;

    // Armamos del Jugador
    auto player = std::make_unique<GameObject>("Player");
    player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
    Vector2{1.0f, 1.0f});
    player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
    SDL_Color{60, 180, 100, 255});
    player->AddComponent<PlayerControllerComponent>(300.0f, true);
    player->AddComponent<ColliderComponent>(Vector2{60.0f, 60.0f});
    ::appstate.entities.push_back(std::move(player));

    // Entidad Obstáculo: reutiliza Transform y RectRender sin necesitar PlayerController
    auto obstacle = std::make_unique<GameObject>("Obstacle");
    obstacle->AddComponent<TransformComponent>(Vector2{180.0f, 140.0f},
    Vector2{1.5f, 1.5f});
    obstacle->AddComponent<RectRenderComponent>(Vector2{80.0f, 80.0f},
    SDL_Color{220, 70, 70, 255});
    obstacle->AddComponent<ColliderComponent>(Vector2{80.0f, 80.0f});
    ::appstate.entities.push_back(std::move(obstacle));

    auto ball = std::make_unique<GameObject>("Ball");
    ball->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f}, Vector2{1.0f, 1.0f});
    ball->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
    SDL_Color{240, 210, 60, 255});
    ball->AddComponent<ColliderComponent>(Vector2{24.0f, 24.0f});
    ball->AddComponent<BallComponent>();
    ::appstate.entities.push_back(std::move(ball));
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *app = static_cast<AppState *>(appstate);

    // 1. Medición de Delta Time en segundos
    Uint64 current_ticks = SDL_GetTicks();
    float delta_time = static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
    app->last_ticks = current_ticks;

    // Evitar saltos de tiempo excesivos si el sistema operativo pausa el proceso
    if (delta_time > 0.05f)
    {
        delta_time = 0.05f;
    }

    // 2. Fase de Actualización (Update)
    
    // Fase de Actualización
    constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
    app->physics_accumulator += delta_time;
    while (app->physics_accumulator >= FIXED_TIMESTEP)
    {
        for (auto &entity : app->entities)
        {
            entity->Update(FIXED_TIMESTEP);
        }
        app->collisionManager.CheckCollisions();
        app->physics_accumulator -= FIXED_TIMESTEP;
    }
    // Fase de Renderizado
    SDL_SetRenderDrawColor(app->renderer, 25, 25, 30, 255);
    SDL_RenderClear(app->renderer);
    for (auto &entity : app->entities)
    {
        entity->Render(app->renderer);
    }
    if (app->debug_draw)
    {
        for (auto &entity : app->entities)
        {
            if (auto *col = entity->GetComponent<ColliderComponent>())
            {
            col->RenderDebug(app->renderer);
            }
        }
    }
    SDL_RenderPresent(app->renderer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.scancode == SDL_SCANCODE_F1)
    {
        if (app)
        {
        app->debug_draw = !app->debug_draw;
        SDL_Log("Debug Draw: %s", app->debug_draw ? "ACTIVADO" :
        "DESACTIVADO");
        }
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (app)
    {
        app->entities.clear();
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
    }
    SDL_Quit();
}

void SDL_LogPlatformInfo()
{
    SDL_Log("Plataforma: %s", SDL_GetPlatform());
    SDL_Log("Cores lógicos de CPU: %d", SDL_GetNumLogicalCPUCores());
    SDL_Log("RAM total: %d MB", SDL_GetSystemRAM());
    SDL_Log("Driver de video: %s", SDL_GetCurrentVideoDriver());
}