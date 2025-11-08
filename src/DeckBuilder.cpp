#include "../include/DeckBuilder.h"
#include "../include/CardFactory.h"
#include <algorithm>
#include <random>

std::vector<std::unique_ptr<Card>> DeckBuilder::buildStarterDeck() {
    std::vector<std::unique_ptr<Card>> deck;
    // Упрощённый старт: 8 Scout (trade 1) и 2 Fighter
    for (int i = 0; i < 8; ++i) {
        deck.push_back(CardFactory::create(CardType::Scout));
    }
    for (int i = 0; i < 2; ++i) {
        deck.push_back(CardFactory::create(CardType::Fighter));
    }
    // Перемешать: используем shuffle (клонировать не нужно — уникальные объекты)
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    return deck;
}
