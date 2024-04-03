#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card {
private:
    string suit;
    string rank;
    int value;

public:
    // Constructor
    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}

    // Getters
    string getSuit() const { return suit; }
    string getRank() const { return rank; }
    int getValue() const { return value; }

    // Setters
    void setSuit(string s) { suit = s; }
    void setRank(string r) { rank = r; }
    void setRank(int v) { value = v; }
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
    const vector<Card>& getCards() const { return cards; }

    // Setter (optional)
    void setCards(const vector<Card>& newCards) { cards = newCards; }
};



// Declare function to place a bet
int placeYourBet(int, int);

// Declare function to deal a card
void dealCard(vector<Card> &stack, vector<Card> &hand);

// Declare function to clear the player's and dealer's hand after a round ends
void clearHands(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit);

// Declare function to get the curent score of a hand
int scoreHand(vector<Card> &hand);

// Declare a function to reshuffle the card stack
void reshuffleStack(vector<Card> &stack, DeckOfCards);


int main() {
    // Create a new deck of cards
    const int STARTING_PIONTS = 1000;   // starting value of the player's points
    const int MAX_BET = 100;            // value of the maximum amount the player will be allowed to bet.
    int numOfDecks = 0;                 // used for the player to choose how many decks of cards they want in the stack of cards
    int randomCard;                     // used to generate a random number for the index of the cardStack vector
    int playerTotal = 0;                // used to keep a total of the player's hand
    int dealerTotal = 0;                // used to keep a total of the dealer's hand
    int playerBet = 0;                  // amount of points the player wants to bet each hand
    int playerSplitBet = 0;             // amount of points the player will bet on the 2nd hand of a split
    int playerBank = STARTING_PIONTS;   // used for live total of the player's available points
    vector<Card> cardStack;             // vector for the entire set of cards
    vector<Card> playerHand;            // vector for the cards in the player's hand
    vector<Card> playerSplitHand;       // vector for the cards in the player's 2nd hand from a split
    vector<Card> dealerHand;            // vector for the cards in the dealer's hand

    cout << "Welcome to Blackjack!" << endl;
    cout << "This game uses traditional casino rules for a single player" << endl;
    cout << "to play blackjack against the house (the computer)." << endl;
    cout << endl;
    cout << "How many decks of cards do you want in the stack (1-6): ";
    cin >> numOfDecks;
    while ((numOfDecks < 1) || (numOfDecks > 6)) {
        cout << endl;
        cout << "Invalid entry.  Please enter the number of decks from 1-6: ";
        cin >> numOfDecks;
    }

    DeckOfCards deck(numOfDecks);

    // Load the cards into the dealing stack
    cardStack = deck.getCards();

    playerBet = placeYourBet(playerBank, MAX_BET);

/***************** Uncomment this section to print the full deck of cards *********************
    cout << "Cards in the deck:" << endl;
    for (const auto& card : cardStack) {
        cout << card.getRank() << " of " << card.getSuit() << " value = " << card.getValue() << endl;
    }
****************** Uncomment this section to print the full deck of cards *********************/

    cout << endl << endl;

// Deal beginning cards - player, dealer, player, dealer
    srand(time(0));
    randomCard = (rand()%(cardStack.size()));
    playerHand.push_back(cardStack.at(randomCard));
    cardStack.erase((cardStack.begin() + randomCard));
    randomCard = (rand()%(cardStack.size()));
    dealerHand.push_back(cardStack.at(randomCard));
    cardStack.erase((cardStack.begin() + randomCard));
    randomCard = (rand()%(cardStack.size()));
    playerHand.push_back(cardStack.at(randomCard));
    cardStack.erase((cardStack.begin() + randomCard));
    randomCard = (rand()%(cardStack.size()));
    dealerHand.push_back(cardStack.at(randomCard));
    cardStack.erase((cardStack.begin() + randomCard));

    cout << "BET = " << playerBet << endl;
    cout << "PLAYER HAND                                        DEALER HAND" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < playerHand.size(); i++) {
        cout << playerHand.at(i).getRank() << " of " << playerHand.at(i).getSuit() << "                                         "
             << dealerHand.at(i).getRank() << " of " << dealerHand.at(i).getSuit() << endl;
        playerTotal += playerHand.at(i).getValue();
        dealerTotal += dealerHand.at(i).getValue();
    }

    cout << endl;
    cout << "     " << playerTotal << "                                                   " << dealerTotal << endl;

// Deal 4 more cards to the player's hand
    cout << endl << endl;
    dealCard(cardStack, playerHand);
    cout << playerHand.at(playerHand.size()-1).getRank() << " of " << playerHand.at(playerHand.size()-1).getSuit() << endl;
    dealCard(cardStack, playerHand);
    cout << playerHand.at(playerHand.size()-1).getRank() << " of " << playerHand.at(playerHand.size()-1).getSuit() << endl;
    dealCard(cardStack, playerHand);
    cout << playerHand.at(playerHand.size()-1).getRank() << " of " << playerHand.at(playerHand.size()-1).getSuit() << endl;
    dealCard(cardStack, playerHand);
    cout << playerHand.at(playerHand.size()-1).getRank() << " of " << playerHand.at(playerHand.size()-1).getSuit() << endl;
    cout << endl;
// Output the score of the player's hand (first 2 cards & additional 4 cards)
    cout << "SCORE = " << scoreHand(playerHand);
    cout << endl << endl;
// Clear everything from the hand vectors
    clearHands(dealerHand, playerHand, playerSplitHand);
    cout << dealerHand.size() << "  " << playerHand.size() << "  " << playerSplitHand.size() << endl; // All vectors should be size 0
    cout << endl << endl;
    cout << "Before reshuffle = " << cardStack.size() << endl;   // Size of stack before reshuffle
    reshuffleStack(cardStack, deck);
    cout << "After reshuffle = " << cardStack.size() << endl;   // Size of stack after reshuffle

    return 0;
}

// Function for player to place a bet
int placeYourBet(int availablePoints, int maxBet) {
    int inputBet;
    if (availablePoints < maxBet) {
        maxBet = availablePoints;
    }
    cout << endl;
    cout << "You have " << availablePoints << " points available." << endl;
    cout << "you may bet 1 to " << maxBet << " points." << endl;
    cout << "Enter 0 to end the game." << endl;
    cout << "How many points would you like to bet? ";
    cin >> inputBet;
    while ((inputBet < 0) || (inputBet > maxBet)) {
        cout << endl;
        cout << "Invalid entry!" << endl;
        cout << "your bet must be between 1 and " << maxBet << " points." << endl;
        cout << "How many points would you like to bet? ";
        cin >> inputBet;
    }
    if (inputBet == 0) {
        cout <<endl;
        cout << "Thank you for playing." << endl;
        cout << endl;
        exit(0);
    }
    return inputBet;
}

// Function to deal a card to a hand
void dealCard(vector<Card> &stack, vector<Card> &hand) {
    int randomCard = (rand()%(stack.size()));
    hand.push_back(stack.at(randomCard));
    stack.erase((stack.begin() + randomCard));
    return;
}

// Function to clear all hands
void clearHands(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit) {
    handDealer.clear();
    handPlayer.clear();
    handSplit.clear();
    return;
}

// Function to get the current hand score
int scoreHand(vector<Card> &hand) {
    int score = 0;
    for (int i = 0; i < hand.size(); i++) {
        score += hand.at(i).getValue();
    }
    return score;
}

void reshuffleStack(vector<Card> &stack, DeckOfCards newDeck) {
    stack.clear();
    stack = newDeck.getCards();
    return;
}


/*

cardStack.size();			// Return the current number of cards in the stack
playerHand.clear();			// Clear all the cards from the player's hand before the next hand
dealerHand.clear();			// Clear all the cards from the dealer's hand before the next hand
cardStack.clear();			// Clear all the cards out of the stack (do this prior to a reshuffle)
cardStack = deck.getCards();// Fill the stack with all the cards from the number of decks choosen (acts as a reshuffle)

*/
