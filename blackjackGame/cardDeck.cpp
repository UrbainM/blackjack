#include "cardDeck.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

Card::Card(std::string s, std::string r) : suit(s), rank(r) {}

std::string Card::getSuit() const {
    return suit;
}

std::string Card::getRank() const {
    return rank;
}

void Card::setSuit(std::string s) {
    suit = s;
}

void Card::setRank(std::string r) {
    rank = r;
}

DeckOfCards::DeckOfCards() {
    std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                                      "Jack", "Queen", "King", "Ace"};
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            cards.push_back(Card(suit, rank));
        }
    }
}

void DeckOfCards::shuffle() {
    std::mt19937 g(std::time(nullptr)); // Mersenne Twister random number generator shuffles based on seed of current time.
    std::shuffle(cards.begin(), cards.end(), g);
}

Card DeckOfCards::dealCard() {
    if (cards.empty()) {
        std::cerr << "Deck is empty!" << std::endl;
        return Card("", "");
    }

    Card dealtCard = cards.back();
    cards.pop_back();
    // Check if remaining cards fall below 10% of the total deck size;
    if (cards.size() < 0.1 * 52) {
        std::cout << "Reshuffling the deck..." << std::endl;
        shuffle();
    }

    return dealtCard;
}

const std::vector<Card>& DeckOfCards::getCards() const {
    return cards;
}

void DeckOfCards::setCards(const std::vector<Card>& newCards) {
    cards = newCards;
}

/*
int main() {
// Create a new deck of cards
    DeckOfCards deck;
// Get the cards from the deck
    const vector<Card>& cards = deck.getCards();
// Print the cards in the deck
    cout << "Cards in the deck:" << endl;
    for (const auto& card : cards) {
        cout << card.getRank() << " of " << card.getSuit() << endl;
    }
    return 0;
}
*/
