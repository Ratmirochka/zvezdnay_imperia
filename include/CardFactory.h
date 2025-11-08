#pragma once
#include "Card.h"
#include <memory>

class CardFactory {
public:
    // Фабричный метод — создаёт прототип-объект (можно расширять новыми типами)
    static std::unique_ptr<Card> create(CardType t);
};
