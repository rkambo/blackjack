#include "../include/cards.hpp"
#include <string.h>

using namespace std;

enum State {NORMAL, BLACKJACK, BUST, PUSH, DEALERWIN};

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
int handTotal(bool aceAlwaysOne, std::vector<Deck::Card> * hand) {
    std::vector<int> values;
    int total = 0;
    for(Deck::Card card : (*hand)) {
        values.push_back(card.to_value());
    }

    std::sort(values.begin(),values.end(),greater<int>());
    
    for(int rank : values) {
        if(aceAlwaysOne == false and rank == Deck::Card::Ace and (total + 11 <= 21)) {
            total += 11;
        }   
        else total += rank;
    }
    return total;
}

float bustChance(Deck * deck, int total ) {
    double validCards = 0;

    for(auto card : (*deck)) {
        if((total + card.to_value() <= 21)) {
            validCards += 1;
        }
    }
    return (1 - (validCards / deck->size())) * 100;
}
void hit(Deck * d, std::vector<Deck::Card> * hand, Deck::Card * top) {
    (*d).draw(&top);
    (*hand).push_back(*top);
}

State checkBust(bool checkForDealer, int pTotal, int dTotal) {
    int total = checkForDealer ? dTotal : pTotal; 

    if(total > 21) {
        return BUST;
    }
    else if(total == 21) {
        return BLACKJACK;
    }
    else if(checkForDealer) { 
        if(pTotal == dTotal) {
            return PUSH;
        }
        else if(dTotal > pTotal) {
            return DEALERWIN;
        }
    }
        return NORMAL;
    
}
void printMove(bool dealerTurn, State pState) {
    if(dealerTurn) {
        switch(pState) {
            case BUST:
                cout << "Dealer busted! You win!" << endl;
                break;
            case BLACKJACK:
                cout << "Dealer has Blackjack! You lose!" << endl;
                break;
            case PUSH:
                cout << "Push! It's a draw!" << endl;
                break;
            case DEALERWIN:
                cout << "Dealer wins!" << endl;
                break;
            default:
                cout << "PlayerState: " << pState << endl;
        }
    }
    else{
        switch(pState) {
            case BUST:
                cout << "Bust! You lose!" << endl;
                break;
            case BLACKJACK:
                cout << "Blackjack! You win!" << endl;
                break;
            case NORMAL:
                cout << "Hit - H     Stand - S" << endl;
                break;
            default:
                cerr << "Unrecognized state: " << pState << endl;
        }
    }
}

void printHands(bool playerTurn, Deck * deck, std::vector<Deck::Card> * dHand, std::vector<Deck::Card> * pHand) {
    cout << endl;
    cout << (string("Dealer's Hand")).append(17,' ') << "Player's Hand" << endl;
    cout << (string("-------------")).append(17,' ') << "-------------" << endl;
    cout << endl;

    int dHandSize = (*dHand).size();
    int pHandSize = (*pHand).size();
    int maxHandSize = max(dHandSize,pHandSize);

    string cardRow [maxHandSize];

    for( int i = 0; i < dHandSize; i++) {
        if(i == 0 && playerTurn) {
            cardRow[0] = "???";
        }
        else {
            cardRow[i] = (*dHand)[i].to_full_name();
        }
    }

    for(int i = 0; i < pHandSize; i++) {
        cardRow[i] += (*pHand)[i].to_full_name().insert(0, 30 - cardRow[i].length(),' ');
    }
   
    for(int i = 0; i < maxHandSize; i++) {
        cout << cardRow[i] << endl;
    }

    string dealerTotalString = "Dealer Total: " + (playerTurn ? "???" : to_string(handTotal(false, dHand)));
    string playerTotalString = string("Player Total: ").insert(0, 30 - dealerTotalString.length(), ' ') + to_string(handTotal(false, pHand));
    int playerTotal = handTotal(true, pHand);

    cout << endl;
    cout << endl;

    cout << dealerTotalString << playerTotalString << endl;
    if(playerTotal < 21) {
        cout << "Bust Probability: " << bustChance(deck, playerTotal) << "%" << endl;
    }
    cout << endl;
    cout << "*************************************************" << endl;
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
    bool turnOver = false;
    State gameState;

    // Deal out
    hit(&d,&dealerCards,top);
    hit(&d,&dealerCards,top);

    hit(&d,&playerCards,top);
    hit(&d,&playerCards,top);
    
    printHands(1, &d,&dealerCards, &playerCards);
    gameState = checkBust(0, handTotal(false, &playerCards), handTotal(false, &dealerCards));
    printMove(0,gameState);
    if(gameState != NORMAL) {
        return 0;
    }
    char input;

    while(turnOver == false) {
        cin >> input;
        switch(input) {
            case 'h':
            case 'H':
                hit(&d,&playerCards,top);
                printHands(1, &d,&dealerCards, &playerCards);
                gameState = checkBust(0, handTotal(false, &playerCards), handTotal(false, &dealerCards));
                printMove(0,gameState);
                if(gameState != NORMAL) {
                    turnOver = true;
                }
                break;
            case 's':
            case 'S':
                gameState = checkBust(1, handTotal(false, &playerCards), handTotal(false, &dealerCards));
                while(gameState == NORMAL) {
                    hit(&d,&dealerCards,top);
                    gameState = checkBust(1, handTotal(false, &playerCards), handTotal(false, &dealerCards));
                }
                printHands(0, &d,&dealerCards, &playerCards);
                printMove(1, gameState);
                if(gameState != NORMAL) {
                    turnOver = true;
                }
                break;
            default:
                cout << "Invalid input! Please try again!" << endl;
        }
    }
    delete top;
    return 0;
}