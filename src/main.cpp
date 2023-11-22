#include "../include/cards.hpp"

using namespace std;

void printHeader() {
    cout << "*************************************************" << endl;
    cout << " ____  _            _        _            _ " << endl
            << "|  _ \\| |          | |      | |          | |"   << endl
            << "| |_) | | __ _  ___| | __   | | __ _  ___| | __" << endl
            << "|  _ <| |/ _` |/ __| |/ /   | |/ _` |/ __| |/ /" << endl
            << "| |_) | | (_| | (__|   < |__| | (_| | (__|   < "<< endl
            << "|____/|_|\\__,_|\\___|_|\\_\\____/ \\__,_|\\___|_|\\_\\" << endl;

    cout << "*************************************************" << endl;
}

void printHands(bool firstTurn, std::vector<Deck::Card> * dHand, std::vector<Deck::Card> * pHand) {
    cout << endl;
    cout << "Dealer's Hand" << endl;
    cout << "-------------" << endl;
    cout << endl;

    for( int i = 0; i < (*dHand).size(); i++) {
        if(i == 0 && firstTurn) {
            cout << "???" << endl;
        }
        else {
            cout << (*dHand)[i].to_full_name((*dHand)[i]) << endl;
        }
    }

    cout << endl;
    cout << "Player's Hand" << endl;
    cout << "-------------" << endl;
    cout << endl;

    for( auto card : (*pHand)) {
        cout << card.to_full_name(card) << endl;    
    }
}

int main() {

    printHeader();
    
    // Prepare deck
    Deck d;
    d.shuffleDeck();
    Deck::Card *top = (Deck::Card *) ::operator new(sizeof(Deck::Card));
    std::vector<Deck::Card> dealerCards;
    std::vector<Deck::Card> playerCards;

    // Deal out
    d.draw(&top);
    dealerCards.push_back(*top);
    d.draw(&top);
    dealerCards.push_back(*top);

    d.draw(&top);
    playerCards.push_back(*top);
    d.draw(&top);
    playerCards.push_back(*top);

    // cout << dealerCards.back().to_full_name(dealerCards.back());
    printHands(1, &dealerCards, &playerCards);
    
    // while(true) {
    //     d.draw(&top);
    //     if(top == nullptr) {
    //         break;
    //     }
    //     cout << (*top).to_full_name(*top) << endl;
    // } 

    // delete top;

    return 0;
}