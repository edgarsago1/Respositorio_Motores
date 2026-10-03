#include "../../include/Engine/TriangleRenderComponent.hpp"

#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/ShipControllerComponent.hpp"
#include <vector>
SDL_Vertex vertex[3];

void TriangleRenderComponent::Render(SDL_Renderer *renderer){

    if (!owner) return;
    // Consultamos la posición y escala al TransformComponent de nuestra entidad
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    ShipControllerComponent *ship = owner->GetComponent<ShipControllerComponent>();
    if(!transform || !ship) return;
    vertex[0] = {transform->position.x + (ship->getOrientation().x * size.x/2), transform->position.y + (ship->getOrientation().y * size.y/2)};
    vertex[0].color =  vertexColor;
    std::vector<Vector2> triangle_vertex = ship->getTriangleVertex();
    vertex[1] = {transform->position.x + (triangle_vertex[0].x * size.x/2), transform->position.y + (triangle_vertex[0].y * size.y/2)}; 
    vertex[1].color =  vertexColor;
    vertex[2] = {transform->position.x + (triangle_vertex[1].x * size.x/2), transform->position.y + (triangle_vertex[1].y * size.y/2)}; 
    vertex[2].color =  vertexColor;
    SDL_RenderGeometry(renderer, nullptr, vertex, 3, nullptr, 0);
}