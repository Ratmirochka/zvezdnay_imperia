#include "../include/Game.h"
#include "../include/CardFactory.h"
#include <iostream>
#include <limits>

// Singleton accessor: возвращает ссылку на единственный объект
Game& Game::instance() {
    static Game instance; // локальный статический объект — инициализируется один раз
    return instance;
}

// Конструктор — приватный (вызывается единожды при первой вызове instance())
Game::Game() : p1("Игрок 1"), p2("Игрок 2") {
    setupMarket();
}

void Game::setupMarket() {
    market.clear();
    market.push_back(CardFactory::create(CardType::TradeShip));
    market.push_back(CardFactory::create(CardType::Fighter));
    market.push_back(CardFactory::create(CardType::InfluenceCard));
    market.push_back(CardFactory::create(CardType::Scout));
    market.push_back(CardFactory::create(CardType::TradeShip));
}

void Game::refillMarket() {
    while (market.size() < 5) {
        market.push_back(CardFactory::create(CardType::Scout));
    }
}

void Game::showStatus() {
    std::cout << "\n=== Состояние игры ===\n";
    std::cout << p1.name << " | Влияние: " << p1.influence
              << " | Колода: " << p1.deck.size()
              << " | Сброс: " << p1.discard.size()
              << " | Карты в руке: " << p1.hand.size() << "\n";

    std::cout << p2.name << " | Влияние: " << p2.influence
              << " | Колода: " << p2.deck.size()
              << " | Сброс: " << p2.discard.size()
              << " | Карты в руке: " << p2.hand.size() << "\n";

    std::cout << "\nТорговый ряд:\n";
    for (size_t i = 0; i < market.size(); ++i) {
        std::cout << i << ": " << market[i]->info() << "\n";
    }
    std::cout << "======================\n";
}

void Game::run() {
    Player* current = &p1;
    Player* other = &p2;
    int turn = 1;

    while (p1.influence > 0 && p2.influence > 0) {
        std::cout << "\n===== Ход " << turn << " =====\n";
        showStatus();
        playerTurn(*current, *other);

        if (p1.influence <= 0 || p2.influence <= 0) break;

        std::swap(current, other);
        ++turn;
    }

    if (p1.influence <= 0) std::cout << "\nПобедил " << p2.name << "!\n";
    else if (p2.influence <= 0) std::cout << "\nПобедил " << p1.name << "!\n";
    else std::cout << "\nИгра завершена.\n";
}

void Game::playerTurn(Player &pl, Player &opponent) {
    pl.tradeRes = 0;
    pl.combatRes = 0;

    std::cout << "\nХод игрока: " << pl.name << "\n";
    std::cout << "Ваши карты в руке:\n";
    for (size_t i=0; i < pl.hand.size(); ++i){
        std::cout << i << ": " << pl.hand[i]->info() << "\n";
    }

    std::cout << "\nСыграть все карты? (y/n): ";
    char c;
    std::cin >> c;

    if (c == 'y' || c == 'Y') {
        playAll(pl);
    } else {
        std::cout << "Введите индекс карты для розыгрыша (или -1 чтобы пропустить): ";
        int idx;
        std::cin >> idx;
        if (idx >= 0 && idx < (int)pl.hand.size()) {
            auto card = std::move(pl.hand[idx]);
            pl.hand.erase(pl.hand.begin() + idx);
            pl.tradeRes += card->trade;
            pl.combatRes += card->combat;
            pl.influence += card->influence;
            pl.discard.push_back(std::move(card));
            std::cout << "Карта сыграна. Торговля: " << pl.tradeRes
                      << " | Атака: " << pl.combatRes << "\n";
        } else {
            std::cout << "Пропуск розыгрыша.\n";
        }
    }

    attemptBuy(pl);
    attemptAttack(pl, opponent);

    pl.tradeRes = 0;
    pl.combatRes = 0;
    pl.discardHand();
    pl.drawToHand(5);
    refillMarket();
}

void Game::playAll(Player &pl) {
    for (auto &card : pl.hand) {
        pl.tradeRes += card->trade;
        pl.combatRes += card->combat;
        pl.influence += card->influence;
        pl.discard.push_back(card->clone());
    }
    pl.hand.clear();

    std::cout << "Все карты сыграны! Торговля: " << pl.tradeRes
              << " | Атака: " << pl.combatRes
              << " | Влияние: +" << pl.influence << "\n";
}

void Game::attemptBuy(Player &pl) {
    if (pl.tradeRes <= 0) {
        std::cout << "\nУ вас нет торговых очков для покупки.\n";
        return;
    }

    std::cout << "\nДоступно торговли: " << pl.tradeRes << "\n";
    std::cout << "Введите индекс карты для покупки или -1 чтобы пропустить: ";

    int idx;
    std::cin >> idx;

    if (idx >= 0 && idx < (int)market.size()) {
        if (market[idx]->cost <= pl.tradeRes) {
            pl.tradeRes -= market[idx]->cost;
            pl.gainToDiscard(market[idx]->clone());
            std::cout << "Вы купили карту: " << market[idx]->name << "\n";

            market.erase(market.begin() + idx);
            market.push_back(CardFactory::create(CardType::Scout));
        } else {
            std::cout << "Недостаточно торговых очков!\n";
        }
    } else {
        std::cout << "Покупка пропущена.\n";
    }
}

void Game::attemptAttack(Player &pl, Player &opponent) {
    if (pl.combatRes <= 0) {
        std::cout << "У вас нет очков атаки.\n";
        return;
    }

    std::cout << "\nУ вас " << pl.combatRes << " очков атаки. Сколько нанести урона? (0 чтобы пропустить): ";
    int dmg;
    std::cin >> dmg;

    if (dmg > 0 && dmg <= pl.combatRes) {
        opponent.influence -= dmg;
        pl.combatRes -= dmg;
        std::cout << "Атака проведена! " << opponent.name << " теряет " << dmg << " влияния.\n";
    } else {
        std::cout << "Атака пропущена.\n";
    }
}
