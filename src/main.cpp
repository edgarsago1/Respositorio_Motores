#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Vector2.hpp"

void SDL_LogPlatformInfo(); 

//Variable para detectar el modo ratón, que permite al cuadrado perseguir al cursor.
bool mouse_mode = false;
// Hacemos un modelo más modular, ahora creamos una estructura personaje donde guardar posición y velocidad.
struct Character{
    Vector2 position{440.0f, 240.0f};
    Vector2 size{60.0f, 60.0f};
    float speed{300.0f};
    SDL_Color color{60, 180, 100, 255};
    // Nueva función que nos permite obtener la posición del centro del personaje, la posición es medida desde la esquina superior del objeto 
    // Calculamos donde estaría el centro del personaje tomando en cuenta su tamaño.
    Vector2 getCenter() const
    {
        return {
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f
        };
    }
};
void PhysicsUpdate(Character &character, const Vector2 &direction, float fixed_dt){
    Vector2 save_character_pos = character.position; // guardamos la posición inicial del personaje antes de actualizar
    character.position = character.position + (direction * (character.speed * fixed_dt));
    Vector2 new_center = character.getCenter();
    /*
    Esto es lo que mantiene adentro de la ventana al personaje, calculamos si la posición futura del personaje se encontrara fuera de los
    límites de nuestra ventana a traves de los bordes de la caja
    */
    if(new_center.x + (character.size.x/2) > 960.0f || 0 > new_center.x -(character.size.x/2))
        character.position.x = save_character_pos.x;
    if(new_center.y + (character.size.y/2) > 540.0f || 0 > new_center.y -(character.size.y/2))
        character.position.y = save_character_pos.y;
}

struct AppState
{
    SDL_Renderer *renderer{nullptr};
    SDL_Window *window{nullptr};

    // Temporizador para Delta Time
    Uint64 last_ticks{0};

    Character player;
    float physics_accumulator{0.0f};
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
    // TODO (Paso 2): Obtener el estado del teclado con SDL_GetKeyboardState y mover el rectángulo.
    // 2. Fase de Actualización (Update)
    const bool *keys = SDL_GetKeyboardState(nullptr);
    
    // Se presiona 1 para alternar entre el modo ratón y el modo tecla.
    if(keys[SDL_SCANCODE_1])
        mouse_mode = !mouse_mode;
    //Ahora hacemos el seguimiento del input mediante un vector que a la vez indica el movimiento del personaje
    Vector2 input_dir{0.0f, 0.0f};
    //Se presiona una tecla, hacemos la indicación de a que dirección se dirige el personaje
    if(!mouse_mode){
        if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
            input_dir.y -= 1.0;
        if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
            input_dir.y += 1.0;
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
            input_dir.x -= 1.0;
        if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
            input_dir.x += 1.0;
    } else {
        float mouse_x;
        float mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        Vector2 mouse_pos = {mouse_x, mouse_y};
        // La diferencia entre la posición del personaje y la del mouse nos dan el vector que describe el movimiento del personaje
        Vector2 distancia = mouse_pos - app->player.position;
        if (distancia.length_squared() > 400)
            input_dir = distancia.normalized();
    }

    // Esto es lo que arregla el bug de la diagonal al convertir la magnitud de todos los vectores en 1.
    if (input_dir.length_squared() > 0.0f)
        input_dir = input_dir.normalized();

    //
    constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
    app->physics_accumulator += delta_time;
    while (app->physics_accumulator >= FIXED_TIMESTEP){
        PhysicsUpdate(app->player, input_dir, FIXED_TIMESTEP);
        app->physics_accumulator -= FIXED_TIMESTEP;
    }

    // 3. Fase de Renderizado
    SDL_SetRenderDrawColor(app->renderer, 30, 30, 35, 255);
    SDL_RenderClear(app->renderer);

    // Dibujar el rectángulo del jugador
    SDL_SetRenderDrawColor(app->renderer, 60, 180, 100, 255);
    // Le mandamos ahora los elementos del vector de posición para que sea dibujado
    SDL_FRect player_rect{app->player.position.x, app->player.position.y, app->player.size.x, app->player.size.y};
    SDL_RenderFillRect(app->renderer, &player_rect);

    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (app)
    {
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