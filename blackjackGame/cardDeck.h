#ifndef CARDDECK_H
#define CARDDECK_H

#include <string>
#include <vector>

class Card {
private:
    std::string suit;
    std::string rank;

public:
    Card(std::string s, std::string r);
    std::string getSuit() const;
    std::string getRank() const;
    void setSuit(std::string s);
    void setRank(std::string r);
};

class DeckOfCards {
private:
    std::vector<Card> cards;

public:
    DeckOfCards();
    void shuffle();
    Card dealCard();
    const std::vector<Card>& getCards() const;
    void setCards(const std::vector<Card>& newCards);
};

#endif // CARDDECK_H
