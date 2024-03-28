#include <iostream>
#include "hand.h"

int main() {
    Hand playerHand;
    Hand dealerHand;

    DeckOfCards deck;
    deck.shuffle();

    Card playerCard1 = deck.dealCard();
    playerHand.addCard(playerCard1.getRank(), playerCard1.getSuit());
    Card playerCard2 = deck.dealCard();
    playerHand.addCard(playerCard2.getRank(), playerCard2.getSuit());

    if (playerHand.hasBlackjack() == true){
        std::cout << "\x1B[31mPlayer Wins\x1B[0m\t" << std::endl;
    }

}
