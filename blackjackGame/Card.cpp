#include "Card.h"

Card::Card(string s, string r, int v) {
    suit = s;
    rank = r;
    value = v;
}

// Getters
string Card::getSuit() { return suit; }
string Card::getRank() { return rank; }
int Card::getValue() { return value; }

// Setters
void Card::setSuit(string s) { suit = s; }
void Card::setRank(string r) { rank = r; }
void Card::setValue(int v) { value = v; }

