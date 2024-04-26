#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "Card.h"
using namespace std;


class DeckOfCards {
private:
    vector<Card> cards;

public:
    DeckOfCards(int decks);
    const vector<Card>& getCards();
    void setCards(const vector<Card>& newCards);
    void shuffleDeck();
};

#endif // DECKOFCARDS_H
