#include "../include/Card.h"
#include <sstream>

std::string Card::info() const {
    std::ostringstream ss;
    ss << name << " (cost:" << cost
       << " trade:" << trade
       << " combat:" << combat
       << " inf:" << influence << ")";
    return ss.str();
}
