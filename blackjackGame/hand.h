#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>
#include <map>
#include "cardDeck.h"

class Hand {
private:
    std::vector<Card> cards;
    std::map<std::string, int> cardValues;

public:
    // Constructor
    Hand();

    // Add a card to the hand
    void addCard(const std::string& value, const std::string& suit);

    // Calculate total value of the hand
    int calculateTotal() const;

    // Check if the hand has a blackjack
    bool hasBlackjack() const;

    // Check if the hand has busted
    bool isBusted() const;

    // Show total value of the hand
    void showTotal() const;

    // Get all cards in the hand
    const std::vector<Card>& getCards() const { return cards; }
};

#endif // HAND_H
