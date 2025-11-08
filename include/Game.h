#pragma once
#include "Player.h"
#include "Card.h"
#include <vector>
#include <memory>

class Game {
public:
    Player p1;
    Player p2;
    std::vector<std::unique_ptr<Card>> market; // торговый ряд (5 карт)
    Game();
    void setupMarket();
    void refillMarket();
    void run(); // основной цикл игры
private:
    void showStatus();
    void playerTurn(Player &active, Player &opponent);
    void playAll(Player &pl);
    void attemptBuy(Player &pl);
    void attemptAttack(Player &pl, Player &opponent);
};
