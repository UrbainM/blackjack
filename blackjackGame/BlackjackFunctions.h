#ifndef BLACKJACKFUNCTIONS_H
#define BLACKJACKFUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <thread>


// Function to get numerical input from the user **************************
int getIntInput(const string& prompt) {
    int userInput;
    while (true) {
        cout << prompt;
        cin >> userInput;

        // Check if input failed or if input is out of range
        if (cin.fail()) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << endl;
            cout << "Your entry was not a number.  Please try again." << endl;
            cout << endl;
        } else {
            break;  // Input is valid, break out of the loop
        }
    }
    return userInput;
}


// Function for player to place a bet *************************
int placeYourBet(int availablePoints, int maxBet, bool *cheat) {
    int inputBet;
    if (availablePoints < maxBet) {
        maxBet = availablePoints;
    }
    cout << endl;
    cout << "You have " << availablePoints << " points available." << endl;
    cout << "you may bet 1 to " << maxBet << " points." << endl;
    cout << "Enter 0 to end the game." << endl;
    cout << endl;
    inputBet = getIntInput("How many points would you like to bet? (0 to exit): ");
    if (*cheat == false && inputBet == 12345) {
        *cheat = true;
        cout << endl;
        cout << "CHEAT CODE IS ACTIVATED!!!" << endl;
        cout << "You will now be asked to choose the rank of every card delt." << endl;
        cout << "You will need to enter - 2, 3, 4, 5, 6, 7, 8, 9 ,10, Jack, Queen, King, Ace." << endl;
        cout << endl;
        cout << "Now enter your actual bet." << endl;
        inputBet = getIntInput("How many points would you like to bet? (0 to exit): ");
    }
    if (*cheat == true && inputBet == 54321) {
        *cheat = false;
        cout << endl;
        cout << "CHEAT CODE IS DEACTIVATED!!!" << endl;
        cout << endl;
        cout << "Now enter your actual bet." << endl;
        inputBet = getIntInput("How many points would you like to bet? (0 to exit): ");
    }
    while ((inputBet < 0) || (inputBet > maxBet)) {
        cout << endl;
        cout << "Invalid entry!" << endl;
        cout << "your bet must be between 1 and " << maxBet << " points." << endl;
        inputBet = getIntInput("How many points would you like to bet? (0 to exit): ");
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
void dealCard(vector<Card> &stack, vector<Card> &hand, bool cheat, bool cardToPlayer) {
    if (!cheat) {
        int randomCard = (rand()%(stack.size()));   // used to generate a random number for the index of the cardStack vector
        hand.push_back(stack.at(randomCard));
        stack.erase((stack.begin() + randomCard));
    }
    else {
        string cheatCard;
        string cardToDeal;
        bool cardFound = false;
        if (cardToPlayer) {
            cardToDeal = "player";
        }
        else {
            cardToDeal = "dealer";
        }
        cout << endl;
        cout << "*** Choose a card for the " << cardToDeal << ": ";
        cin >> cheatCard;
        while ((cheatCard != "2") && (cheatCard != "3") && (cheatCard != "4") && (cheatCard != "5") && (cheatCard != "6") && (cheatCard != "7")
               && (cheatCard != "8") && (cheatCard != "9") && (cheatCard != "10") && (cheatCard != "Jack") && (cheatCard != "Queen") && (cheatCard != "King")
               && (cheatCard != "Ace")) {
            cout << "Your entry is not recognized.  Try again: ";
            cin >> cheatCard;
        }
        while (!cardFound) {
            for (unsigned int i = 0; i < stack.size(); i++){
                if (stack.at(i).getRank() == cheatCard) {
                    hand.push_back(stack.at(i));
                    stack.erase((stack.begin() + i));
                    cardFound = true;
                    i = stack.size();
                }
            }
            if (!cardFound) {
                cout << "There are no more " << cheatCard << "'s in the stack." << endl;
                cout << "Choose a different card. ";
                cin >> cheatCard;
                while ((cheatCard != "2") && (cheatCard != "3") && (cheatCard != "4") && (cheatCard != "5") && (cheatCard != "6") && (cheatCard != "7")
                       && (cheatCard != "8") && (cheatCard != "9") && (cheatCard != "10") && (cheatCard != "Jack") && (cheatCard != "Queen") && (cheatCard != "King")
                       && (cheatCard != "Ace")) {
                    cout << "Your entry is not recognized.  Try again: ";
                    cin >> cheatCard;
                }
            }
        }
    }
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
    for (unsigned int i = 0; i < hand.size(); i++) {
        score += hand.at(i).getValue();
    }
    return score;
}


// Function to change the value of an Ace from 11 to 1 ********************
void changeAce(vector<Card> &hand) {
    for (unsigned int i = 0; i < hand.size(); i++){
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
    for (unsigned int i = 0; i < handPlayer.size(); i++) {
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
    for (unsigned int i = 0; i < handDealer.size(); i++) {
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
    for (unsigned int i = 0; i < handPlayer.size(); i++) {
        cout << setw(6) << right << handPlayer.at(i).getRank() << " of " << handPlayer.at(i).getSuit() << endl;
    }
    cout << endl << endl;
    cout << "YOUR SPLIT BET = " << splitBet << endl << endl;
    cout << "PLAYER'S SPLIT HAND - Total = " << scoreHand(handSplit) << endl;
    cout << "----------------------------" << endl;
    for (unsigned int i = 0; i < handSplit.size(); i++) {
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
    for (unsigned int i = 0; i < handDealer.size(); i++) {
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


#endif // BLACKJACKFUNCTIONS_H
