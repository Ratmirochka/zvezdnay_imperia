#include "../include/Card.h"
#include <sstream>

std::string Card::info() const {
    std::ostringstream ss;
    ss << name << " (Цена: " << cost
       << " | Торговля: " << trade
       << " | Атака: " << combat
       << " | Влияние: " << influence << ")";
    return ss.str();
}
