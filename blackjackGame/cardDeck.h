#ifndef CARDDECK_H
#define CARDDECK_H

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
    DeckOfCards();
    // Getters
    const vector<Card>& getCards() const { return cards; }
    // Setter (optional)
    void setCards(const vector<Card>& newCards) { cards = newCards; }
};

#endif // CARDDECK_H
