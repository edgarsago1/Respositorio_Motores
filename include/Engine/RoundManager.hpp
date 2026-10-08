#pragma once

class GameScene;
class ShipControllerComponent;
class RoundManager{
    private:
        int current_round{0}; // Guardamos el número de rondas
        int score{0};   // Guardamos el score total
        int asteroids_count{7}; // Número de Asteroides generados en total por cada asteroid de 3 stages
        GameScene* m_scene{nullptr}; // Puntero a la escena de ejecución para crear asteroides
        ShipControllerComponent* m_ship{nullptr}; //Puntero al jugador para crear periodos de invisibilidad entre rondas
        int lives{2}; // Contador de vidas
        int wait_beforeRound{100};
        int current_wait{100};
    public:
        RoundManager() = default;

        void SetScene(GameScene* scene){
            m_scene = scene;
        }

        void SetShip(ShipControllerComponent* ship){
            m_ship = ship;
        }

        // Se encarga de crear nuevos enemigos cada una de las rondas.
        void StartRound();

        //Maneja eventos especiales dentro de la ronda (por el momento solo maneja no haber enemigos)
        void manageRounds();

        // Pensado para devolver el score actual del juego
        int getScore() const;

        //Pensado para devolver el score final del juego (Bonificación de multiplicación por ronda)
        int getFinalScore() const;

        // Pensado para devolver la ronda actual del juego
        int getRounds() const;

        // Pensado para modificar el score de acuerdo al asteroide destruido
        void sumScore(int stage);

        // Resta la cantidad de vidas del jugador en esa sesión de juego
        void LostLife();

        // Determina si se termina la partida si no hay vidas
        bool IsDefeated() const;
};