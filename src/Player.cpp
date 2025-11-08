#include "../include/Player.h"
#include "../include/DeckBuilder.h"
#include <algorithm>
#include <random>
#include <iostream>

Player::Player(std::string n) : name(std::move(n)) {
    deck = DeckBuilder::buildStarterDeck();
    drawToHand(5); // стартовая рука
}

Player::~Player() = default;

void Player::shuffleDiscardToDeck() {
    if (discard.empty()) return;
    // перемешиваем discard и переносим в deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(discard.begin(), discard.end(), g);
    for (auto &c : discard) deck.push_back(std::move(c));
    discard.clear();
}

std::unique_ptr<Card> Player::drawOne() {
    if (deck.empty()) {
        shuffleDiscardToDeck();
    }
    if (deck.empty()) return nullptr;
    auto card = std::move(deck.back());
    deck.pop_back();
    return card;
}

void Player::drawToHand(int N) {
    for (int i = 0; i < N; ++i) {
        auto c = drawOne();
        if (c) hand.push_back(std::move(c));
    }
}

void Player::discardHand() {
    for (auto &c : hand) discard.push_back(std::move(c));
    hand.clear();
}

void Player::gainToDiscard(std::unique_ptr<Card> card) {
    discard.push_back(std::move(card));
}
