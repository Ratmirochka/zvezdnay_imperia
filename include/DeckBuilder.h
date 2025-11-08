#pragma once
#include "Card.h"
#include <vector>
#include <memory>

class DeckBuilder {
public:
    // Возвращает вектор уникальных_ptr карт — стартовая колода (клонирует прототипы)
    static std::vector<std::unique_ptr<Card>> buildStarterDeck();
};
