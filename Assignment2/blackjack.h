#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector> // #include directive
#include <string>

enum Rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
EIGHT, NINE, TEN, JACK, QUEEN, KING};

enum Type {CLUBS, DIAMONDS, HEARTS, SPADES};
class Card {

    private:
        Rank aRank;
        Type aType;

    public:
        Card(Rank pRank, Type pType);
        int getValue() const;
        void displayCard() const;
};

class Hand {
    private:
        std::vector<Card> aHand;
    public:
        void add(Card card);

        void clear();

        int getTotal() const;

        void displayHand() const;
};

class Deck {
    private:
        std::vector<Card> aDeck;
    
    public:
        void populate();

        void shuffle();

        void deal(Hand &pHand);
};

class AbstractPlayer : public Hand {
    public:
        virtual bool isDrawing() const = 0;
        virtual void displayPlayer() const = 0;
        bool isBusted();
};

class HumanPlayer : public AbstractPlayer { 
    public:
        HumanPlayer();
        bool isDrawing() const;

        void displayPlayer() const;
};

class ComputerPlayer : public AbstractPlayer { 
    public:
        bool isDrawing() const;

        void displayPlayer() const;
};

class BlackJackGame {
    public:
        Deck m_deck;
        ComputerPlayer m_casino;
        void play();
};
#endif