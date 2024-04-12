#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <thread>
#include <random>
#include <algorithm>

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
    void setValue(int v) { value = v; }
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

    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
};



// Declare function to place a bet
int placeYourBet(int, int);

// Declare function to deal a card
void dealCard(vector<Card> &stack, vector<Card> &hand);

// Declare function to clear the player's and dealer's hand after a round ends
void clearHands(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit);

// Declare function to get the curent score of a hand
int scoreHand(vector<Card> &hand);

// Declare function to change the value of an Ace from 11 to 1
void changeAce(vector<Card> &hand);

// Declare a function to reshuffle the card stack
void reshuffleStack(vector<Card> &stack, DeckOfCards);

// Declare a function to display the cards on the table - overload for split
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, int bet, bool stay);
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit, int bet, int splitBet, bool stay, bool splitStay);


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
    bool stand = false;                 // bool to use for the player to stand or not - also used to skip other play options
    bool splitStand = false;            // bool to use for the player to stand or not on the split hand - also used to skip other play options
    bool playerBust = false;            // bool used to indicate if the player's hand is bust or not
    bool playerSplitBust = false;       // bool used to indicate if the player's split hand is bust or not
    bool dealerBlackjack = false;       // bool used to indicate that the dealer has blackjack and skips other play options
    bool playerBlackjack = false;       // bool used to indicate that the player has blackjack and skips other play options
    char playerChoice;                  // char used for player to enter game choices
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
        cin >> numOfDecks;
        if(cin.fail()) { // entering a non-integer entered infinite loop
            cin.clear(); // clear the error flags
            cin.ignore(); // ignore any characters in the input buffer
            cout << "Invalid input. Please enter an integer (1-6)." << endl;
        }
    }

    DeckOfCards deck(numOfDecks);

    // Shuffle the deck
    deck.shuffleDeck();

    // Load the cards into the dealing stack
    cardStack = deck.getCards();

    while(true) {

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
        dealCard(cardStack, playerHand);
        dealCard(cardStack, dealerHand);
        dealCard(cardStack, playerHand);
        dealCard(cardStack, dealerHand);

        while (!stand) {
            displayTable(dealerHand, playerHand, playerBet, stand);
            if (scoreHand(playerHand) > 21) {
                changeAce(playerHand);
                displayTable(dealerHand, playerHand, playerBet, stand);
            }

            if (scoreHand(dealerHand) > 21) {
                changeAce(dealerHand);
                displayTable(dealerHand, playerHand, playerBet, stand);
            }

            cout << endl << endl;
            if (dealerHand.at(0).getRank() == "Ace") {
                if ((scoreHand(playerHand) == 21) && (scoreHand(dealerHand) == 21)) {
                    cout << endl;
                    cout << "Both the player and dealer have blackjack." << endl;
                    cout << "This hand is a push - no winner." << endl << endl;
                    break;
                }
                else {
                    if (playerBank > (round(playerBet * 0.5))) {
                        cout << endl;
                        cout << "Dealer is showing an Ace." << endl;
                        cout << "Would you like to buy insurance against" << endl;
                        cout << "the dealer having blackjack (y/n)? ";
                        cin >> playerChoice;
                        while ((tolower(playerChoice) != 'y') && (tolower(playerChoice) != 'n')) {
                            cout << "Your entry was not recognized.  Try again: ";
                            cin >> playerChoice;
                        }
                        if (tolower(playerChoice) == 'y') {
                            cout << endl;
                            cout << "You purchased insurance." << endl;
                            cout << "You do not lose your bet." << endl << endl;
                            playerBank -= round(playerBet * 0.5);
                            break; // Exit the loop after the insurance decision is made
                        }
                    }
                    else {
                        cout << endl;
                        playerChoice = 'n';
                        cout << "Dealer is showing an Ace." << endl;
                        cout << "You do not have enough points to buy insurance." << endl;
                        system("pause");
                    }

                    if (scoreHand(dealerHand) == 21) {
                        dealerBlackjack = true;
                        stand = true;
                        displayTable(dealerHand, playerHand, playerBet, stand);
                        cout << endl;
                        cout << "Dealer has blackjack" << endl;
                        if (playerChoice == 'y') {
                            cout << endl;
                            cout << "You purchased insurance." << endl;
                            cout << "You do not loose your bet." << endl << endl;
                            playerBank = playerBank - (round(playerBet * 0.5));
                        }
                        else {
                            cout << endl;
                            cout << "You did not purchase insurance." << endl;
                            cout << "Dealer wins." << endl << endl;
                            playerBank = playerBank - playerBet;
                        }
                    }
                    else {
                        cout << endl;
                        cout << "Dealer does not have blackjack" << endl;
                        cout << "play on this hand will continue." << endl << endl;
                    }
                }
            }
            if (scoreHand(playerHand) == 21) {
                if (scoreHand(dealerHand) == 21) {
                    cout << endl;
                    cout << "Both the player and dealer have blackjack." << endl;
                    cout << "This hand is a push - no winner." << endl << endl;
                    dealerBlackjack = true;
                    playerBlackjack = true;
                }
                else {
                    cout << endl;
                    cout << "You have blackjack!" << endl;
                    cout << "You win 1.5x your bet = " << (playerBet * 1.5) << endl << endl;
                    playerBank = playerBank + (playerBet * 1.5);
                    playerBlackjack = true;
                    break;
                }
            }
            if ((!dealerBlackjack) && (!playerBlackjack)) {
                cout << "Would you like to hit or stand (h/s)? ";
                cin >> playerChoice;
                while ((tolower(playerChoice) != 'h') && (tolower(playerChoice) != 's')) {
                    cout << "Your entry was not recognized.  Try again: ";
                    cin >> playerChoice;
                }
                if (playerChoice == 'h') {
                    dealCard(cardStack, playerHand);
                    if (scoreHand(playerHand) > 21) {
                        changeAce(playerHand);
                    }
                }
                else {
                    stand = true;
                }
                if (scoreHand(playerHand) > 21) {
                    playerBust = true;
                    stand = true;
                }
                displayTable(dealerHand, playerHand, playerBet, stand);
            }
        }
        if (!dealerBlackjack) {
            if (playerBust) {
                cout << endl;
                cout << "Player Busts - Dealer wins." << endl << endl;
                playerBank = playerBank - playerBet;
            }

            if (!playerBust) {
                while (scoreHand(dealerHand) < 17) {
                    dealCard(cardStack, dealerHand);
                    if (scoreHand(dealerHand) > 21) {
                        changeAce(dealerHand);
                    }
                    displayTable(dealerHand, playerHand, playerBet, stand);
                }
                if (scoreHand(dealerHand) > 21) {
                    cout << endl;
                    cout << "Dealer Busts - Player wins." << endl << endl;
                    playerBank = playerBank + playerBet;
                }
                else {
                    if (scoreHand(playerHand) == scoreHand(dealerHand)) {
                        cout << endl;
                        cout << "Push - no winner." << endl << endl;
                    }
                    else if (scoreHand(playerHand) > scoreHand(dealerHand)) {
                        cout << endl;
                        cout << "Player wins." << endl << endl;
                        playerBank = playerBank + playerBet;
                    }
                    else {
                        cout << endl;
                        cout << "Dealer wins." << endl << endl;
                        playerBank = playerBank - playerBet;
                    }
                }
            }
        }
        stand = false;
        splitStand = false;
        playerBust = false;
        playerSplitBust = false;
        dealerBlackjack = false;
        clearHands(dealerHand, playerHand, playerSplitHand);
        if (cardStack.size() < 20) {
            reshuffleStack(cardStack, deck);
        }
    }

    return 0;
}

// Function for player to place a bet *************************
int placeYourBet(int availablePoints, int maxBet) {
    int inputBet;
    if (availablePoints < maxBet) {
        maxBet = availablePoints;
    }
    cout << endl;
    cout << "You have " << availablePoints << " points available." << endl;
    cout << "you may bet 1 to " << maxBet << " points." << endl;
    cout << "Enter 0 to end the game." << endl;
    cout << endl;
    cout << "How many points would you like to bet? ";
    cin >> inputBet;

    while ((inputBet < 0) || (inputBet > maxBet)) {
        cin.clear(); // avoiding input buffer errors
        cin.ignore(); // avoiding input buffer errors
        cout << endl;
        cout << "Invalid entry!" << endl;
        cout << "your bet must be between 1 and " << maxBet << " points." << endl;
        cout << endl;
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

// Function to deal a card to a hand ***************************
void dealCard(vector<Card> &stack, vector<Card> &hand) {
    int randomCard = (rand()%(stack.size()));
    hand.push_back(stack.at(randomCard));
    stack.erase((stack.begin() + randomCard));
    return;
}

// Function to clear all hands *********************************
void clearHands(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit) {
    handDealer.clear();
    handPlayer.clear();
    handSplit.clear();
    return;
}

// Function to get the current hand score ***********************
int scoreHand(vector<Card> &hand) {
    int score = 0;
    for (int i = 0; i < hand.size(); i++) {
        score += hand.at(i).getValue();
    }
    return score;
}

// Function to change the value of an Ace from 11 to 1 ********************
void changeAce(vector<Card> &hand) {
    for (int i = 0; i < hand.size(); i++){
        if ((hand.at(i).getRank() == "Ace") && (hand.at(i).getValue() == 11)) {
            hand.at(i).setValue(1);
            i = hand.size();
        }
    }
    return;
}

// Function to reshuffle the card stack **************************
void reshuffleStack(vector<Card> &stack, DeckOfCards newDeck) {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    cout << "Time to reshuffle.  The next hand will be played with a new stack." << endl;
    cout << endl;
    cout << "Reshuffling.";
    stack.clear();
    stack = newDeck.getCards();
    std::random_device rd; // Obtain a random seed
    std::mt19937 rng(rd()); // Initialize the Mersenne Twister pseudo-random number generator
    for (int i = 1; i < 21; i++) {
        std::shuffle(stack.begin(), stack.end(), rng); // Shuffle the card stack
        cout << ".";
        sleep_for(milliseconds(500));
    }
    cout << endl << endl;
    return;
}

// Function to display the card table **************************
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, int bet, bool stay) {
    system("cls");
    cout << "YOUR BET = " << bet << endl << endl;
    cout << "PLAYER'S HAND - Total = " << scoreHand(handPlayer) << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < handPlayer.size(); i++) {
        cout << setw(6) << right << handPlayer.at(i).getRank() << " of " << handPlayer.at(i).getSuit() << endl;
    }
    cout << endl << endl;
    if (!stay) {
        cout << "DEALER'S HAND" << endl;
    }
    else {
        cout << "DEALER'S HAND - Total = " << scoreHand(handDealer) << endl;
    }
    cout << "----------------------------" << endl;
    for (int i = 0; i < handDealer.size(); i++) {
        if ((!stay) && (i ==(handDealer.size() - 1))) {
            cout << setw(11) << right << "-DOWN-" << endl;
        }
        else {
            cout << setw(6) << right << handDealer.at(i).getRank() << " of " << handDealer.at(i).getSuit() << endl;
        }
    }
    cout << endl;
    return;
}

