#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

class Deck {
    public:
        class Card {
            public:
                enum Suit {Hearts, Diamonds, Spades, Clubs};
                enum Rank {
                    Ace = 1,
                    Two = 2,
                    Three = 3,
                    Four = 4,
                    Five = 5,
                    Six = 6,
                    Seven = 7,
                    Eight = 8,
                    Nine = 9,
                    Ten = 10,
                    Jack = 11,
                    Queen = 12,
                    King = 13
                    };
            private:
                Rank rank;
                Suit suit;
            public:
                Card(Suit i_suit, Rank i_rank) {
                    rank = i_rank;
                    suit = i_suit;
                }
                Rank get_rank(){
                    return rank;
                }
                Suit get_suit(){
                    return suit;
                }
                std::string to_name() {
                    switch (rank) {
                        case Ace:
                            return "Ace";
                        case Two:
                            return "Two";
                        case Three:
                            return "Three";
                        case Four:
                            return "Four";
                        case Five:
                            return "Five";
                        case Six:
                            return "Six";
                        case Seven:
                            return "Seven";
                        case Eight:
                            return "Eight";
                        case Nine:
                            return "Nine";
                        case Ten:
                            return "Ten";
                        case Jack:
                            return "Jack";
                        case Queen:
                            return "Queen";
                        case King:
                            return "King";
                    }
                }

                int to_value() {
                    if(rank == Jack || rank == Queen || rank == King) {
                        return 10;
                    }
                    else {
                        return rank;
                    }
                }

                std::string to_suit() {
                    switch(suit) {
                        case Hearts:
                            return "Hearts";
                        case Diamonds:
                            return "Diamonds";
                        case Spades:
                            return "Spades";
                        case Clubs:
                            return "Clubs";
                    }
                }

                std::string to_full_name() {
                    return to_name() + " of " + to_suit();
                }
        };
    private:
        std::vector<Card> deck;
        std::vector<Card> discard;
    public:
        Deck() {
            createDeck();
        }

        void printDeck() {
            for(Deck::Card card: deck) {
                std::cout << card.to_full_name() << std::endl;
            }
        }

        void createDeck() {
            for(int in_suit = 0; in_suit < 4; in_suit++) {
                for(int in_rank = 1; in_rank <= 13; in_rank++) {
                    Card card(static_cast<Card::Suit>(in_suit), static_cast<Card::Rank>(in_rank));
                    deck.push_back(card);
                }
            }
        }

        std::vector<Deck::Card>::iterator begin() { return deck.begin(); }
        std::vector<Deck::Card>::iterator end(){ return deck.end(); }

        int size() {
            return deck.size();
        }

        void shuffleDeck() {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle (deck.begin(), deck.end(), std::default_random_engine(seed));
        }

        void draw(Card ** top) {
            if(deck.size() == 0) {
                deck.insert(deck.end(), discard.begin(), discard.end());
                discard.erase(discard.begin(), discard.end());
            }
            **top = deck.back();
            deck.pop_back();
        }

        void flush(std::vector<Card> * toFlush) {
            discard.insert(discard.end(), (*toFlush).begin(), (*toFlush).end());
            (*toFlush).erase((*toFlush).begin(), (*toFlush).end());
        }
};
