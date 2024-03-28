#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>
#include <map>

class Hand {
private:
    struct Card {
        int value;
        std::string suit;
    };
    std::vector<Card> cards;  // Stores the cards in the hand
    std::map<std::string, int> cardValues; // Map to store card values

public:
    Hand();  // Constructor
    void addCard(const std::string& value, const std::string& suit);  // Add a card to the hand
    int calculateTotal() const;  // Calculate the total value of the hand
    bool hasBlackjack() const;  // Check if the hand is a natural blackjack
    void showTotal() const; // Show the total value of the hand
};

#endif
