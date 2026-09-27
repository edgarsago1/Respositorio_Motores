#define SDL_MAIN_USE_CALLBACKS 1

// Bibliotecas externas
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Importación de clases
#include "core/Vector2.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/SceneManager.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/PauseScene.hpp"

void SDL_LogPlatformInfo(); 

void SceneManager::RestartGame() {
    ChangeScene(std::make_unique<GameScene>(this, "GameScene"));
}

void SceneManager::ShowTitle() {
    ChangeScene(std::make_unique<TitleScene>(this, "TitleScene"));
}

void SceneManager::ShowGameOver() {
    PushScene(std::make_unique<GameOverScene>(this, "GameOverScene"));
}

void SceneManager::ShowPause() {
    PushScene(std::make_unique<PauseScene>(this, "PauseScene"));
}

struct AppState
{
    SDL_Renderer *renderer{nullptr};
    SDL_Window *window{nullptr};

    // Temporizador para Delta Time
    Uint64 last_ticks{0};
    // Modo de depuración visual para inspeccionar colisionadores
    SceneManager sceneManager;

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

    if (!SDL_CreateWindowAndRenderer("Práctica 05", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al crear ventana o renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

    ::appstate.window = window;
    ::appstate.renderer = renderer;
    ::appstate.last_ticks = SDL_GetTicks();
    ::appstate.sceneManager.ChangeScene(std::make_unique<TitleScene>(&::appstate.sceneManager, "TitleScene"));
    ::appstate.sceneManager.ProcessPendingChanges();
    *appstate = &::appstate;
    
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
    //Procesar los cambios de escenas
    app->sceneManager.ProcessPendingChanges();
    app->sceneManager.Update(delta_time);
    app->sceneManager.Render(app->renderer);
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
    if (app && app->sceneManager.HasScenes()){
        app->sceneManager.HandleEvent(*event);
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (app)
    {
        app->sceneManager.Clear();
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