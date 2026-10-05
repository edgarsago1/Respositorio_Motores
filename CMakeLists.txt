cmake_minimum_required(VERSION 3.16)
project(proyecto1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscamos SDL3

# Seguimos la siguiente instrucción para encontrar SDLs
find_package(SDL3 CONFIG REQUIRED)
# find_package(SDL3 QUIET)
# if(NOT SDL3_FOUND)
#    find_package(PkgConfig REQUIRED)
#    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
#    set(SDL3_TARGET PkgConfig::SDL3)
# else()
#    set(SDL3_TARGET SDL3::SDL3)
# endif()

# Generamos el ejecutable con el nombre del proyecto
add_executable(${PROJECT_NAME}
src/main.cpp
src/Engine/BallComponent.cpp
src/Engine/GameObject.cpp
src/Engine/PlayerControllerComponent.cpp
src/Engine/RectRenderComponent.cpp
src/Engine/Scene.cpp
src/Engine/SceneManager.cpp
src/Engine/TransformComponent.cpp
src/Engine/ShipControllerComponent.cpp
src/Engine/TriangleRenderComponent.cpp
src/Engine/ProjectileComponent.cpp
src/Game/GameOverScene.cpp
src/Game/GameScene.cpp
src/Game/PauseScene.cpp
src/Game/TitleScene.cpp
src/Math/Vector2.cpp
src/Physics/ColliderComponent.cpp
src/Physics/CollisionManager.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET})
