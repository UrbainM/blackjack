#include "DeckOfCards.h"

DeckOfCards::DeckOfCards(int decks) {
    // Initialize the deck with all 52 standard playing cards
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i=1; i<= decks; i++) {
        for (const auto& suit : suits) {
            int v = 0;
            for (const auto& rank : ranks) {
                cards.push_back(Card(suit, rank, values[v]));
                ++v;
            }
        }
    }
}

// Getters
const vector<Card>& DeckOfCards::getCards() { return cards; }

// Setter (optional)
void DeckOfCards::setCards(const vector<Card>& newCards) { cards = newCards; }

void DeckOfCards::shuffleDeck() {
    std::random_device rd; // Random number generator
    std::mt19937 g(rd()); // 32-bit Mersenne Twister Pseudorandom number generator
    std::shuffle(cards.begin(), cards.end(), g);
}
