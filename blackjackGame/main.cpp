#include <iostream>
#include "hand.h"

int main() {
    Hand playerHand;
    Hand dealerHand;

    playerHand.addCard("10","Hearts");
    playerHand.addCard("Ace","Spades");

    if (playerHand.hasBlackjack() == true){
        std::cout << "\x1B[31mPlayer Wins\x1B[0m\t" << std::endl;
    }

}
