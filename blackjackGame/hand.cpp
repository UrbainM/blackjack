#include "Hand.h"
#include <iostream>

Hand::Hand() {
    cards.clear();

    // Initialize card values
    cardValues["2"] = 2;
    cardValues["3"] = 3;
    cardValues["4"] = 4;
    cardValues["5"] = 5;
    cardValues["6"] = 6;
    cardValues["7"] = 7;
    cardValues["8"] = 8;
    cardValues["9"] = 9;
    cardValues["10"] = 10;
    cardValues["Jack"] = 10;
    cardValues["Queen"] = 10;
    cardValues["King"] = 10;
    cardValues["Ace"] = 11;
}

void Hand::addCard(const std::string& value, const std::string& suit) {
    cards.push_back({cardValues[value], suit});
}

int Hand::calculateTotal() const {
    int total = 0;
    int numAces = 0;

    for (const auto& card : cards) {
        total += card.value;
        if (card.value == 11) {  // Ace
            numAces++;
        }
    }

    // Adjust total for Aces if necessary
    while (total > 21 && numAces > 0) {
        total -= 10;  // Change Ace from 11 to 1
        numAces--;
    }

    return total;
}

bool Hand::hasBlackjack() const {
    return cards.size() == 2 && calculateTotal() == 21;
}

void Hand::showTotal() const {
    std::cout << "Total: " << calculateTotal() << std::endl;
}
