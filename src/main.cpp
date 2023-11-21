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

void printHands() {
    cout << endl;
    cout << "Dealer's Hand" << endl;
    cout << "-------------" << endl;
    cout << endl;
}

int main() {

    printHeader();
    
    // Prepare deck
    Deck d;
    d.shuffleDeck();
    Deck::Card *top = (Deck::Card *) ::operator new(sizeof(Deck::Card));
    std::vector<Deck::Card> dealerCards;
    std::vector<Deck::Card> playerCards;

    for (Deck::Card c : dealerCards) {
        cout << c.to_full_name(c) << endl;
    }
    // cout << dealerCards.back().to_full_name(dealerCards.back());
    // printHands();
    
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