#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card {
private:
    string suit;
    string rank;
    int value;

public:
    // Constructor
    Card(string s, string r, int v);

    // Getters
    string getSuit();
    string getRank();
    int getValue();

    // Setters
    void setSuit(string s);
    void setRank(string r);
    void setValue(int v);
};

#endif // CARD_H
