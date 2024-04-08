#include <iostream>
#include <string>

class Player {
public:
    int bankroll;

    // Constructor to inititialize the plyer's bankroll
    Player() : bankroll(1000) {}

    // Function to place a bet
    bool placeBet(int betAmount) {
        if (betAmount > 100) {
            std::cout << "Maximum bet is 100 points.\n";
            return false;
        } else if (betAmount > bankroll) {
            std::cout << "Insufficient points. Your bankroll is: " << bankroll << "\n";
            return false;
        } else if (betAmount <= 0) {
            std::cout << "Game ends as the bet is 0 or less.\n";
            return false;
        }
        bankroll -= betAmount;
        return true;
    }

    // Function to update bankroll after a win
    void winPoints(int points) {
        bankroll += points;
    }

    // Function for a push, where no points are won or lost
    void push() {
        std::cout << "It's a push. No points are won or lost.\n";
    }

    // Function to check if the player has 0 points
    bool isBankrupt() {
        return bankroll <= 0;
    }
};

int main() {
    Player player;

    // Example gameplay
    int betAmount;
    std::cout << "Place your bet: ";
    std::cin >> betAmount;

    if (!player.placeBet(betAmount)) {
        // Handle invalid bet
        return 0;
    }

    // Simulate game outcome
    int outcome;
    std::cout << "Enter game outcome (1: Win, 2:lose, 3: Push): ";
    std::cin >> outcome;

    switch(outcome) {
        case 1: // Win
            player.winPoints(betAmount * 2); // Assuming a 1:1 payout
            break;
        case 2: // Lose
            // No action needed, bet amount already deducted
            break;
        case 3: // Push
            player.push();
            player.bankroll += betAmount; // Return the bet
            break;
        default:
            std::cout << "Invalid game outcome.\n";
    }

    std::cout << "Current bankroll: " << player.bankroll << "\n";
    if (player.isBankrupt()) {
        std::cout << "Game over. You have 0 points.\n";
    }

    return 0;
}
