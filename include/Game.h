#pragma once
#include "Player.h"
#include "Card.h"
#include <vector>
#include <memory>
#include <string>

class Game {
public:
    // Получить единственный экземпляр Game (Singleton accessor)
    static Game& instance();

    // Запустить игровой цикл (публичный метод для использования)
    void run();

    // Удаляем копирование и перемещение
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

private:
    // Конструктор инициализирует игроков и рынок
    Game();

    // Деструктор — по умолчанию
    ~Game() = default;

    // Состояние игры
    Player p1;
    Player p2;
    std::vector<std::unique_ptr<Card>> market; // торговый ряд (5 карт)

    // Вспомогательные методы
    void setupMarket();
    void refillMarket();
    void showStatus();
    void playerTurn(Player &active, Player &opponent);
    void playAll(Player &pl);
    void attemptBuy(Player &pl);
    void attemptAttack(Player &pl, Player &opponent);
};
