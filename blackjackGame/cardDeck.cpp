#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Card {
private:
    string suit;
    string rank;
public:
// Constructor
    Card(string s, string r) : suit(s), rank(r) {}
// Getters
    string getSuit() const { return suit; }
    string getRank() const { return rank; }
// Setters
    void setSuit(string s) { suit = s; }
    void setRank(string r) { rank = r; }
};

class DeckOfCards {
private:
    vector<Card> cards;
public:
// Constructor
    DeckOfCards() {
// Initialize the deck with all 52 standard playing cards
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                            "Jack", "Queen", "King", "Ace"};
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            cards.push_back(Card(suit, rank));
                                      }
                                    }
                            }
// Getters
    const vector<Card>& getCards() const { return cards; }
// Setter (optional)
    void setCards(const vector<Card>& newCards) { cards = newCards; }
};
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
