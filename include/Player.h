#pragma once
#include "Card.h"
#include <vector>
#include <memory>
#include <string>

class Player {
public:
    std::string name;
    int influence = 50;
    std::vector<std::unique_ptr<Card>> deck;
    std::vector<std::unique_ptr<Card>> discard;
    std::vector<std::unique_ptr<Card>> hand;
    int tradeRes = 0;
    int combatRes = 0;

    Player(std::string n);
    ~Player();

    void shuffleDiscardToDeck();
    std::unique_ptr<Card> drawOne();
    void drawToHand(int N);
    void discardHand();
    void gainToDiscard(std::unique_ptr<Card> card);
};
