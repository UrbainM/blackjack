#include <iostream>
#include "hand.h"

int main() {
    Hand playerHand;
    Hand dealerHand;

    DeckOfCards deck;
    deck.shuffle();

    Card dealtCard = deck.dealCard();
    playerHand.addCard(dealtCard.getRank(),dealtCard.getSuit());
    dealtCard = deck.dealCard();
    dealerHand.addCard(dealtCard.getRank(),dealtCard.getSuit());
    dealtCard = deck.dealCard();
    playerHand.addCard(dealtCard.getRank(),dealtCard.getSuit());
    dealtCard = deck.dealCard();
    dealerHand.addCard(dealtCard.getRank(),dealtCard.getSuit());


    if (playerHand.hasBlackjack() == true){
        std::cout << "\x1B[31mPlayer Wins\x1B[0m\t" << std::endl;
    }
    std::cout << "Player Hand total: " << playerHand.calculateTotal() << std::endl;
    std::cout << "Dealer Hand total: " << dealerHand.calculateTotal() << std::endl;

    std::cout << "Player's Hand:" << std::endl;
    for (const auto& card : playerHand.getCards()) {
        std::cout << card.getRank() << " of " << card.getSuit() << std::endl;
    }
    std::cout << "Dealer's Hand:" << std::endl;
    for (const auto& card : dealerHand.getCards()) {
        std::cout << card.getRank() << " of " << card.getSuit() << std::endl;
    }

}
