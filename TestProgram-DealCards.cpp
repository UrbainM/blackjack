#include <iostream>
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
    DeckOfCards(int decks) {
        // Initialize the deck with all 52 standard playing cards
        vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
        vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

        for (int i=1; i<= decks; i++) {
            for (const auto& suit : suits) {
                for (const auto& rank : ranks) {
                    cards.push_back(Card(suit, rank));
                }
            }
        }
    }

    // Getters
    const vector<Card>& getCards() const { return cards; }

    // Setter (optional)
    void setCards(const vector<Card>& newCards) { cards = newCards; }
};


int main() {
    // Create a new deck of cards
    int numOfDecks;
    int randomCard;
    vector<Card> cardStack;
    vector<Card> playerHand;
    vector<Card> dealerHand;

    cout << "How many decks of cards do you want in the stack (1-6): ";
    cin >> numOfDecks;

    DeckOfCards deck(numOfDecks);

    // Get the cards from the deck
    cardStack = deck.getCards();

    // Print the cards in the deck
    cout << "Cards in the deck:" << endl;
    for (const auto& card : cardStack) {
        cout << card.getRank() << " of " << card.getSuit() << endl;
    }

    cout << endl << endl;
    cout << "*****************************************************" << endl;

    cout << cardStack.size() << endl << endl;

    srand(time(0));
    for (int i = 0; i < 10 ; i++) {
        randomCard = (rand()%(cardStack.size()));
        playerHand.push_back(cardStack.at(randomCard));
        cardStack.erase((cardStack.begin() + randomCard));
        cout << playerHand.at(i).getRank() << " of " << playerHand.at(i).getSuit() << endl;
    }

    cout << endl;
    cout << cardStack.size();
    cout << endl;
    cardStack.clear();
    cout << cardStack.size();
    cout << endl;
    cardStack = deck.getCards();
    cout << cardStack.size();
    cout << endl;

    return 0;
}
