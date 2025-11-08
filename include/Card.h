#pragma once
#include <string>
#include <memory>

enum class CardType { Scout, Fighter, TradeShip, InfluenceCard };

struct Card {
    std::string name;
    CardType type;
    int cost = 0;
    int trade = 0;   // очки торговли
    int combat = 0;  // очки боя
    int influence = 0; // очки влияния при сыгрывании
    bool isBase = false; // простая метка; в упрощении не используется глубоко

    Card() = default;
    Card(const Card& other) = default;
    virtual ~Card() = default;

    // Прототип: клонирование
    virtual std::unique_ptr<Card> clone() const {
        return std::make_unique<Card>(*this);
    }

    virtual void onPlay() {
        // можно расширить в наследниках
    }

    virtual std::string info() const;
};
