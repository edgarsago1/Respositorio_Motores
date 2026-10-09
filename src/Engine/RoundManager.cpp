#include "../../include/Engine/RoundManager.hpp"

#include <random>
#include "../../include/Engine/RoundManager.hpp"
#include "../../include/Game/GameScene.hpp"
#include "../../include/Engine/ShipControllerComponent.hpp"
#include "../../include/Engine/AsteroidComponent.hpp"
#include "../../include/Engine/GameObject.hpp"
#include "../../include/Engine/TransformComponent.hpp"
#include "../../include/Engine/RectRenderComponent.hpp"
#include "../../include/Math/Vector2.hpp"
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distribution(20, 255);
std::uniform_real_distribution<float> distributionPosX(1.0f, 960.0f);
std::uniform_real_distribution<float> distributionPosY(1.0f, 540.0f);
std::uniform_real_distribution<float> direction(0.0f, 1.0f);
std::uniform_real_distribution<float> size(50.0f, 90.0f); 
SDL_Color color{0, 0, 0, 255};

void RoundManager::StartRound(){
    for(int i = 0; i < current_round*2; i++){
        Vector2 direction{distributionPosX(generator), distributionPosY(generator)};
        direction = direction.normalized();
        color.r = static_cast<Uint8>(distribution(generator));
        color.g = static_cast<Uint8>(distribution(generator));
        color.b = static_cast<Uint8>(distribution(generator));
        float width = size(generator); // Hacemos la dimensión de los asteroides aleatoria
        float height = size(generator); // Hacemos la dimensión de los asteroides aleatoria
        auto asteroid1 = std::make_unique<GameObject>("Asteroid");
        asteroid1->AddComponent<TransformComponent>(Vector2{distributionPosX(generator), distributionPosY(generator)} );
        asteroid1->AddComponent<AsteroidComponent>(2, Vector2{width, height}, direction, 100.0F);
        asteroid1->AddComponent<RectRenderComponent>(Vector2{width, height}, color);
        asteroid1->AddComponent<ColliderComponent>(Vector2{width, height});
        m_scene->Spawn(std::move(asteroid1));
    }

}
void RoundManager::manageRounds(){
    if(!m_scene->StillEnemiesLeft()){
        if(current_wait == wait_beforeRound)
            m_ship->InvincibilityPeriod();
        if(current_wait <= 0){
            current_round++;
            StartRound();
            current_wait = wait_beforeRound;
            return;
        } else {
        current_wait--;
        }
    }
}

void RoundManager::sumScore(int stage){
    switch (stage) {
        case 2:
            score += 10; 
            break;
        case 1:
            score += 20; 
            break;
        case 0:
            score += 30; 
            break;
        default:
            break;
    }
}
int RoundManager::getRounds() const{
    return current_round;
}
int RoundManager::getScore() const{
    return score;
}

int RoundManager::getLives() const{
    return lives;
}

int RoundManager::getFinalScore() const{
    return score * current_round;
}

void RoundManager::LostLife(){
    lives--;
}

bool RoundManager::IsDefeated() const{
    return lives < 0; 
}