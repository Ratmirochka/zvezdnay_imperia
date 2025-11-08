#include "../include/CardFactory.h"
#include <memory>

std::unique_ptr<Card> CardFactory::create(CardType t) {
    using std::make_unique;
    switch (t) {
        case CardType::Scout: {
            auto c = make_unique<Card>();
            c->name = "Scout";
            c->cost = 0;
            c->trade = 1;
            c->combat = 0;
            c->influence = 0;
            return c;
        }
        case CardType::Fighter: {
            auto c = make_unique<Card>();
            c->name = "Fighter";
            c->cost = 3;
            c->trade = 0;
            c->combat = 3;
            c->influence = 0;
            return c;
        }
        case CardType::TradeShip: {
            auto c = make_unique<Card>();
            c->name = "TradeShip";
            c->cost = 4;
            c->trade = 4;
            c->combat = 0;
            c->influence = 0;
            return c;
        }
        case CardType::InfluenceCard: {
            auto c = make_unique<Card>();
            c->name = "Influence";
            c->cost = 5;
            c->trade = 0;
            c->combat = 0;
            c->influence = 5;
            return c;
        }
        default:
            return nullptr;
    }
}
