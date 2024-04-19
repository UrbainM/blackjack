/*
 * Club Paradise
 * 4-29-2024
 * Group Project 2 - Week 15
 * Blackjack Casino Game
 * Software - Beta Test Version
 *
 * Team Members:
 *   David Findley
 *   Jon Heimer
 *   Andrew May
 *   Alexander Smith
 *   Mitchell Urbain
 *
 * Submitted by:
 *   Jon Heimer
 *   jjheimer@dmacc.edu
 *
 * This program will allow a single user to play blackjack
 * against the house (the computer).  It will follow casino
 * rules such as dealer hits on 16 - stays on 17.  Blackjack
 * pays (1.5 x bet).  Player can double down on 9, 10, or 11.
 * Player can split on a pair.
 *
 * This C++ 20 / C++ 17 program is intended for Windows OS as it makes calls to the system for
 *  system("pause") and system("cls") which are different on Linux and Xcode.
 */

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
        std::random_device rd; // Random number generator
        std::mt19937 g(rd()); // 32-bit Mersenne Twister Pseudorandom number generator
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

// Declare a function to display the cards on the table - override for split
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, int bet, bool stay);
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit, int bet, int splitBet, bool stay, bool splitStay);

//Function to get numerical input from the user
int getIntInput(const string& prompt, int min, int max);

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
    bool playerSplit = false;            // bool to use of player choose to split.
    bool splitStand = false;            // bool to use for the player to stand or not on the split hand - also used to skip other play options
    bool playerBust = false;            // bool used to indicate if the player's hand is bust or not
    bool playerSplitBust = false;       // bool used to indicate if the player's split hand is bust or not
    bool dealerBlackjack = false;       // bool used to indicate that the dealer has blackjack and skips other play options
    bool playerBlackjack = false;       // bool used to indicate that the player has blackjack and skips other play options
    bool playerSplitBlackjack = false;  // bool used to indicate that the player split has blackjack and skips other play options
    char playerChoice;                  // char used for player to enter game choices
    vector<Card> cardStack;             // vector for the entire set of cards
    vector<Card> playerHand;            // vector for the cards in the player's hand
    vector<Card> playerSplitHand;       // vector for the cards in the player's 2nd hand from a split
    vector<Card> dealerHand;            // vector for the cards in the dealer's hand

    cout << "Welcome to Blackjack!" << endl << endl;
    cout << "This game uses traditional casino rules for a single player" << endl;
    cout << "to play blackjack against the house (the computer)." << endl;
    cout << endl;

    numOfDecks = getIntInput("How many decks of cards do you want in the stack (1-6): ",1,6);

    DeckOfCards deck(numOfDecks);

    // Shuffle the deck
    deck.shuffleDeck();

    cardStack = deck.getCards();        // Load the cards into the dealing stack

// ******************** THIS IS THE BEGINNING OF THE GAME LOOP ********************
    while(true) {

        playerBet = placeYourBet(playerBank, MAX_BET);

        cout << endl << endl;

// Deal beginning cards - player, dealer, player, dealer
        srand(time(0));
        dealCard(cardStack, playerHand);
        dealCard(cardStack, dealerHand);
        dealCard(cardStack, playerHand);
        dealCard(cardStack, dealerHand);

        displayTable(dealerHand, playerHand, playerBet, stand);

// ******************** CHECH IF DEALER IS SHOWING AN ACE - OFFER INSURANCE ********************
        if (dealerHand.at(0).getRank() == "Ace") {
            if ((scoreHand(playerHand) == 21) && (scoreHand(dealerHand) == 21)) {
                cout << endl;
                cout << "Both the player and dealer have blackjack." << endl;
                cout << "This hand is a push - no winner." << endl << endl;
                stand = true;
                dealerBlackjack = true;
                playerBlackjack = true;
            }
            else {
                if (playerBank >= (round(playerBet * 0.5))) {
                    cout << endl;
                    cout << "Dealer is showing an Ace." << endl;
                    cout << "Would you like to buy insurance against" << endl;
                    cout << "the dealer having blackjack (y/n)? ";
                    cin >> playerChoice;
                    while ((tolower(playerChoice) != 'y') && (tolower(playerChoice) != 'n')) {
                        cout << "Your entry was not recognized.  Try again: ";
                        cin >> playerChoice;
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

// ******************** CHECK IF ONLY THE PLAYER HAS BLACKJACK ********************
        if (!stand) {
            if (scoreHand(playerHand) == 21) {
                playerBlackjack = true;
                stand = true;
                displayTable(dealerHand, playerHand, playerBet, stand);
                cout << endl;
                cout << "You have blackjack!" << endl;
                cout << "You win 1.5x your bet = " << (playerBet * 1.5) << endl << endl;
                playerBank = playerBank + (playerBet * 1.5);
            }
        }

// ******************** CHECK IF THE PLAYER IS ABLE TO DOUBLE-DOWN ********************
        if ((scoreHand(playerHand) >= 9) && (scoreHand(playerHand) <= 11) && (!dealerBlackjack)) {
            if (playerBank >= playerBet) {
                cout << endl;
                cout << "Your hand total is between 9 and 11." << endl;
                cout << "Do you want to double-down (y/n)? ";
                cin >> playerChoice;
                while ((tolower(playerChoice) != 'y') && (tolower(playerChoice) != 'n')) {
                    cout << "Your entry was not recognized.  Try again: ";
                    cin >> playerChoice;
                }
                if (playerChoice == 'y') {
                    playerBet = playerBet * 2;
                    dealCard(cardStack, playerHand);
                    if (scoreHand(playerHand) > 21) {
                        changeAce(playerHand);
                    }
                    stand = true;
                    displayTable(dealerHand, playerHand, playerBet, stand);
                }
            }
            else {
                cout << "Your hand total is between 9 and 11." << endl;
                cout << "You do not have enough points to double-down.";
                system("pause");
            }
        }

// ******************** CHECK IF THE PLAYER IS ABLE TO SPLIT ********************
        if (!stand) {
            if (playerHand.at(0).getRank() == playerHand.at(1).getRank()) {
                if (playerBank >= playerBet) {
                    cout << endl;
                    cout << "You have 2 cards that are the same." << endl;
                    cout << "Do you want to split (y/n)? ";
                    cin >> playerChoice;
                    while ((tolower(playerChoice) != 'y') && (tolower(playerChoice) != 'n')) {
                        cout << "Your entry was not recognized.  Try again: ";
                        cin >> playerChoice;
                    }
                    if (playerChoice == 'y') {
                        playerSplitBet = playerBet;
                        playerSplit = true;
                        playerSplitHand.push_back(playerHand.at(1));
                        playerHand.erase(playerHand.end());
                        dealCard(cardStack, playerHand);
                    }
                }
                else {
                    cout << "You have 2 cards that are the same." << endl;
                    cout << "you do not have enough points to split." << endl;
                    system("pause");
                }
            }
        }

// *************************** Play this section if player does not split hand ********************************
        if (!playerSplit) {
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

                if ((!playerBust) && (!playerBlackjack)) {
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
        }

// ****************************** Play this section if player splits hand ***************************************
        if (playerSplit) {
            if (scoreHand(playerHand) == 21) {
                playerBlackjack = true;
                stand = true;
                displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                cout << endl;
                cout << "Your first hand has blackjack!" << endl;
                cout << "You win 1.5x your bet = " << (playerBet * 1.5) << endl << endl;
                playerBank = playerBank + (playerBet * 1.5);
                system("pause");
            }
            while (!stand) {
                displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);

                if (scoreHand(playerHand) > 21) {
                    changeAce(playerHand);
                    displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                }

                if (scoreHand(dealerHand) > 21) {
                    changeAce(dealerHand);
                    displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                }

                if ((!dealerBlackjack) && (!playerBlackjack)) {
                    cout << "FIRST HAND - Would you like to hit or stand (h/s)? ";
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
                    displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                }
            }

        // *** END PLAYING THE MAIN HAND AND BEGIN PLAYING THE SPLIT HAND ***

            dealCard(cardStack, playerSplitHand);
            while (!splitStand) {
                if (scoreHand(playerSplitHand) == 21) {
                    playerSplitBlackjack = true;
                    splitStand = true;
                    displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                    cout << endl;
                    cout << "Your split hand has blackjack!" << endl;
                    cout << "You win 1.5x your bet = " << (playerSplitBet * 1.5) << endl << endl;
                    playerBank = playerBank + (playerSplitBet * 1.5);
                    system("pause");
                }
                while (!splitStand) {
                    displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                    if (scoreHand(playerSplitHand) > 21) {
                        changeAce(playerSplitHand);
                        displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                    }
                    cout << "SPLIT HAND - Would you like to hit or stand (h/s)? ";
                    cin >> playerChoice;
                    while ((tolower(playerChoice) != 'h') && (tolower(playerChoice) != 's')) {
                        cout << "Your entry was not recognized.  Try again: ";
                        cin >> playerChoice;
                    }
                    if (playerChoice == 'h') {
                        dealCard(cardStack, playerSplitHand);
                        if (scoreHand(playerSplitHand) > 21) {
                            changeAce(playerSplitHand);
                        }
                    }
                    else {
                        splitStand = true;
                    }
                    if (scoreHand(playerSplitHand) > 21) {
                        playerSplitBust = true;
                        splitStand = true;
                    }
                }
            }

            if (!dealerBlackjack) {
                if (playerBust) {
                    cout << endl;
                    cout << "Player's first Hand Busts - Dealer winsagainst this hand." << endl << endl;
                    playerBank = playerBank - playerBet;
                }
                if (playerSplitBust) {
                    cout << endl;
                    cout << "Player's Split Hand Busts - Dealer wins aganst this hand." << endl << endl;
                    playerBank = playerBank - playerSplitBet;
                }

                if (((!playerBust) && (!playerSplitBust)) && ((!playerBlackjack) && (!playerSplitBlackjack))) {
                    while (scoreHand(dealerHand) < 17) {
                        dealCard(cardStack, dealerHand);
                        if (scoreHand(dealerHand) > 21) {
                            changeAce(dealerHand);
                        }
                        displayTable(dealerHand, playerHand, playerSplitHand, playerBet, playerSplitBet, stand, splitStand);
                    }
      //****************************** check if both hands win or just 1 *****************************
                    if (scoreHand(dealerHand) > 21) {
                        cout << endl;
                        if (!playerBust) {
                            cout << "Dealer Busts - Player wins first hand." << endl << endl;
                            playerBank = playerBank + playerBet;
                        }
                    }
                    else {
                        if (scoreHand(playerHand) == scoreHand(dealerHand)) {
                            cout << endl;
                            cout << "Player's first hand is a push - no winner." << endl << endl;
                        }
                        else if (scoreHand(playerHand) > scoreHand(dealerHand)) {
                            cout << endl;
                            cout << "Player's first hand wins." << endl << endl;
                            playerBank = playerBank + playerBet;
                        }
                        else {
                            cout << endl;
                            cout << "Dealer wins against player's first hand." << endl << endl;
                            playerBank = playerBank - playerBet;
                        }
                    }

                    if (scoreHand(dealerHand) > 21) {
                        cout << endl;
                        if (!playerSplitBust) {
                            cout << "Dealer Busts - Player wins split hand." << endl << endl;
                            playerBank = playerBank + playerSplitBet;
                        }
                    }
                    else {
                        if (scoreHand(playerSplitHand) == scoreHand(dealerHand)) {
                            cout << endl;
                            cout << "Player's split hand is a push - no winner." << endl << endl;
                        }
                        else if (scoreHand(playerSplitHand) > scoreHand(dealerHand)) {
                            cout << endl;
                            cout << "Player's split hand wins." << endl << endl;
                            playerBank = playerBank + playerSplitBet;
                        }
                        else {
                            cout << endl;
                            cout << "Dealer wins against player's split hand." << endl << endl;
                            playerBank = playerBank - playerSplitBet;
                        }
                    }
                }
            }
        }
// ****************************** END OF PLAY FOR THIS ROUND ***************************************

// ****************************** REST ALL BOOLEAN FLAGS AND CLEAR ALL HAND VECTORS ***************************************
        stand = false;
        splitStand = false;
        playerSplit = false;
        playerBust = false;
        playerSplitBust = false;
        dealerBlackjack = false;
        playerBlackjack = false;
        playerSplitBlackjack = false;
        clearHands(dealerHand, playerHand, playerSplitHand);
        if (cardStack.size() < 20) {
            reshuffleStack(cardStack, deck);
        }
    }

    return 0;
}
// ******************** END OF MAIN *****************************



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
    inputBet = getIntInput("How many points would you like to bet? (0 to exit):",0,maxBet);
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

// Function to display the card table for standard hand **************************
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

// Function to display the card table for split hand **************************
void displayTable(vector<Card> &handDealer, vector<Card> &handPlayer, vector<Card> &handSplit, int bet, int splitBet, bool stay, bool splitStay) {
    system("cls");
    cout << "YOUR BET = " << bet << endl << endl;
    cout << "PLAYER'S HAND - Total = " << scoreHand(handPlayer) << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < handPlayer.size(); i++) {
        cout << setw(6) << right << handPlayer.at(i).getRank() << " of " << handPlayer.at(i).getSuit() << endl;
    }
    cout << endl << endl;
    cout << "YOUR SPLIT BET = " << bet << endl << endl;
    cout << "PLAYER'S SPLIT HAND - Total = " << scoreHand(handSplit) << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < handSplit.size(); i++) {
        cout << setw(6) << right << handSplit.at(i).getRank() << " of " << handSplit.at(i).getSuit() << endl;
    }

    cout << endl << endl;
    if ((!stay) && (!splitStay)) {
        cout << "DEALER'S HAND" << endl;
    }
    else {
        cout << "DEALER'S HAND - Total = " << scoreHand(handDealer) << endl;
    }
    cout << "----------------------------" << endl;
    for (int i = 0; i < handDealer.size(); i++) {
        if ((!splitStay) && (i == (handDealer.size() - 1))) {
            cout << setw(11) << right << "-DOWN-" << endl;
        }
        else {
            cout << setw(6) << right << handDealer.at(i).getRank() << " of " << handDealer.at(i).getSuit() << endl;
        }
    }
    cout << endl;
    return;
}

int getIntInput(const string& prompt, int min, int max) {
    int userInput;
    while (true) {
        cout << prompt;
        cin >> userInput;

        // Check if input failed or if input is out of range
        if (cin.fail() || userInput < min || userInput > max) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        } else {
            break;  // Input is valid, break out of the loop
        }
    }
    return userInput;
}
