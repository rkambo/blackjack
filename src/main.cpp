#include <iostream>

using namespace std;

struct card {
    int rank;
    int value;
    string suit;
    string name = rank + " of " + suit;
};

int createDeck() {
    card *deck [52];
    const string suits [] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    const string faces [] = {"Jack", "Queen", "King"};

    for(string suit: suits) {
        cout << "Ace" << " of " << suit << endl;
    }

    // Insert normal cards
    for(int i = 2; i <= 10; i++) {
        for(string suit: suits){
            cout << i << " of " << suit << endl;
        }
    }

    for(string face: faces) {
        for(string suit:suits) {
            cout << face << " of " << suit << endl;
        }
    }

    return 1;
};


int main() {
    createDeck();
    return 0;
}