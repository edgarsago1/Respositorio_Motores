cmake_minimum_required(VERSION 3.16)
project(practica06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AddressSanitizer para detección de fugas y corrupción de memoria (opcional / demostrativo)
option(ENABLE_ASAN "Habilitar AddressSanitizer (opcional/demostrativo)" OFF) # No logré cargarlo en mi sistema
if(ENABLE_ASAN)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT WIN32)
message(STATUS "AddressSanitizer (ASan) habilitado: -
fsanitize=address -g")
add_compile_options(-fsanitize=address -g -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)
else()
message(WARNING "AddressSanitizer omitido: no compatible o
susceptible a problemas de enlazado en este entorno.")
endif()
endif()

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

#Buscamos SDL3-image 
find_package(SDL3_image CONFIG REQUIRED)
#if(NOT SDL3_image_FOUND)
#    find_package(PkgConfig REQUIRED)
#    pkg_check_modules(SDL3_IMAGE REQUIRED IMPORTED_TARGET sdl3-image)
#    set(SDL3_IMAGE_TARGET PkgConfig::SDL3_IMAGE)
#else()
#    set(SDL3_IMAGE_TARGET SDL3_image::SDL3_image)
#endif()




# Generamos el ejecutable con el nombre del proyecto
add_executable(${PROJECT_NAME}
src/main.cpp
src/Math/Vector2.cpp
src/Engine/GameObject.cpp
src/Engine/Scene.cpp
src/Engine/SceneManager.cpp
src/Engine/ResourceManager.cpp
src/Engine/Components/TransformComponent.cpp
src/Engine/Components/RectRenderComponent.cpp
src/Engine/Components/PlayerControllerComponent.cpp
src/Engine/Components/SpriteComponent.cpp
src/Engine/Components/ColliderComponent.cpp
src/Physics/CollisionManager.cpp
src/Game/ResourceDemoScene.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

# Copiar directorio de assets al directorio de salida de compilación
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION
${CMAKE_CURRENT_BINARY_DIR})
