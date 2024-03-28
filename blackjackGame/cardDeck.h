#ifndef CARDDECK_H
#define CARDDECK_H

#include <string>
#include <vector>

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
    DeckOfCards();
    // Getters
    const vector<Card>& getCards() const { return cards; }
    // Setter (optional)
    void setCards(const vector<Card>& newCards) { cards = newCards; }
    void shuffle();
    Card dealCard();
};

#endif // CARDDECK_H
