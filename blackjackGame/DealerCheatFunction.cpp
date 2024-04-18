// ******************* THIS FUNCTION REPLACES THE STANDARD dealCard FUNCTION ALLOWING THE PLAYER TO CHEAT AND CHOOSE ALL THE CARDS *******************
// To use this function, copy this into the code and comment out the standard dealCard function
void dealCard(vector<Card> &stack, vector<Card> &hand) {
    string cheatCard;
    bool cardFound = false;
    cout << endl;
    cout << "*** WHAT CARD TO YOU WANT? *** : ";
    cin >> cheatCard;
    while ((cheatCard != "2") && (cheatCard != "3") && (cheatCard != "4") && (cheatCard != "5") && (cheatCard != "6") && (cheatCard != "7")
           && (cheatCard != "8") && (cheatCard != "9") && (cheatCard != "10") && (cheatCard != "Jack") && (cheatCard != "Queen") && (cheatCard != "King")
           && (cheatCard != "Ace")) {
        cout << "Your entry is not recognized.  Try again: ";
        cin >> cheatCard;
    }
    while (!cardFound) {
        for (int i = 0; i < stack.size(); i++){
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
    return;
}

/*

*************************************** POSSIBLE GAME OUTCOMES ***************************************
** Standard Play **
Player has more points than dealer                                              Player wins
Player has less points than dealer                                              Player loses
Player goes over 21 (bust)                                                      Player loses
Dealer goes over 21 (bust)                                                      Player wins
Player and dealer have same score                                               Push (tie)
Player has blackjack - dealer does not                                          Player wins 1.5x
Dealer has blackjack - player does not                                          Player loses
Both player and dealer have blackjack                                           Push (tie)


** Double-Down **
Player has more points than dealer                                              Player wins
Player has less points than dealer                                              Player loses
Dealer goes over 21 (bust)                                                      Player wins
Player and dealer have same score                                               Push (tie)

** Split Hand **
Player First has more points than dealer, Split has more points than dealer     Both hands win
Player First has more points than dealer, Split has less points than dealer     First hand wins, Split hand loses
Player First has less points than dealer, Split has more points than dealer     First hand loses, Split hand wins
Player First has less points than dealer, Split has less points than dealer     Both hands lose
Player First goes over 21 (bust), Split has more points than dealer             First hand loses, Split hand wins
Player First goes over 21 (bust), Split has less points than dealer             Both hands lose
Player First has more points than dealer, Split goes over 21 (bust)             First hand wins, Split hand loses
Player First has less points than dealer, Split goes over 21 (bust)             Both hands lose
Player First and dealer have same score, Split goes over 21 (bust)              First hand Push (tie), Split hand looses
Player First and dealer have same score, Split has more points than dealer      First hand Push (tie), Split hand wins
Player First and dealer have same score, Split has less points than dealer      First hand Push (tie), Split hand looses
Player First and dealer have same score, Split and dealer have same score       First hand Push (tie), Split hand Push (tie)
Player First goes over 21 (bust), Split and dealer have same score              First hand loses, Split hand Push (tie)
Player First has less points than dealer, Split and dealer have same score      First hand loses, Split hand Push (tie)
Player First has more points than dealer, Split and dealer have same score      First hand wins, Split hand Push (tie)
Player First has blackjack, Split has more points than dealer                   First hand wins 1.5x, Split hand wins
Player First has blackjack, Split has less points than dealer                   First hand wins 1.5x, Split hand loses
Player First has blackjack, Split goes over 21 (bust)                           First hand wins 1.5x, Split hand loses
Player First has blackjack, Split has blackjack                                 First hand wins 1.5x, Split hand wins 1.5x
Player First has blackjack, Split and dealer have same score                    First hand wins 1.5x, Split hand Push (tie)
Player First has has more points than dealer, Split has blackjack               First hand wins, Split hand wins 1.5x
Player First has less points than dealer, Split has blackjack                   First hand loses, Split hand wins 1.5x
Player First goes over 21 (bust), Split has blackjack                           First hand loses, Split hand wins 1.5x
Player First and dealer have same score, Split has blackjack                    First hand Push (tie), Split hand wins 1.5x

*/
