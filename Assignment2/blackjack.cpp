#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

enum Rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
EIGHT, NINE, TEN, JACK, QUEEN, KING};

enum Type {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {

    private:
        Rank aRank;
        Type aType;

    public:
        Card(Rank pRank, Type pType) {
            aRank = pRank;
            aType = pType;
        }
        int getValue() const {
            switch(aRank) {
                case ACE:
                    return 1;
                case TWO:
                    return 2;
                case THREE:
                    return 3;
                case FOUR:
                    return 4;
                case FIVE:
                    return 5;
                case SIX:
                    return 6;
                case SEVEN:
                    return 7;
                case EIGHT:
                    return 8;
                case NINE:
                    return 9;
                case TEN:
                    return 10;
                case JACK:
                    return 10;
                case QUEEN:
                    return 10;
                case KING: 
                    return 10;
                default:
                    return 0;   
            }
        }
        void displayCard() const{
            switch(aType) {
                case CLUBS:
                    switch(aRank) {
                        case JACK:
                            cout << "J" << "C";
                            break;
                        case QUEEN:
                            cout << "Q" << "C";
                            break;
                        case KING:
                            cout << "K" << "C";
                            break;
                        default:
                            cout << getValue() << "C";
                    }

                case DIAMONDS:
                    switch(aRank) {
                        case JACK:
                            cout << "J" << "D";
                            break;
                        case QUEEN:
                            cout << "Q" << "D";
                            break;
                        case KING:
                            cout << "K" << "D";
                            break;
                        default:
                            cout << getValue() << "D";
                    }

                case HEARTS:
                    switch(aRank) {
                        case JACK:
                            cout << "J" << "D";
                            break;
                        case QUEEN:
                            cout << "Q" << "D";
                            break;
                        case KING:
                            cout << "K" << "D";
                            break;
                        default:
                            cout << getValue() << "D";
                    }

                case SPADES:
                    switch(aRank) {
                        case JACK:
                            cout << "J" << "S";
                            break;
                        case QUEEN:
                            cout << "Q" << "S";
                            break;
                        case KING:
                            cout << "K" << "S";
                            break;
                        default:
                            cout << getValue() << "S";
                    }
            }
        }
};

class Hand {
    protected:
        vector<Card> aHand;
    
    public:
        void add(Card card) {
            aHand.push_back(card);
        }

        void clear() {
            aHand.clear();
        }

        int getTotal() const {
            bool ace = false;
            int sum = 0;
            for ( auto &i : aHand ) {
                if (i.getValue() == 1) {
                    ace = true;
                }
                sum += i.getValue();
            }

            if (ace && sum + 10 <= 21) {
                return sum + 10;
            }
            else {
                return sum;
            }
        }
};

class Deck {
    private:
        vector<Card> aDeck;
    
    public:
        void populate() {
            aDeck.clear();
            int aRank, aType;
            for (aRank = ACE; aRank <= KING; aRank++) {
                for (aType = CLUBS; aType <= SPADES; aType++) {
                    Card card = Card(Rank(aRank), Type(aType));
                    aDeck.push_back(card);
                }
            }
        }

        void shuffle() {
            random_shuffle(aDeck.begin(), aDeck.end());
        }

        void deal(Hand pHand) {
            Card card = aDeck.back();
            aDeck.pop_back();
            pHand.add(card);
        }
};

class AbstractPlayer : public Hand {
    public:
        virtual bool isDrawing() const = 0;
        virtual void displayHand() const = 0;
        bool isBusted() {
            return getTotal() > 21;
        }
};

class HumanPlayer : public AbstractPlayer { 
    public:
        HumanPlayer() {}
        bool isDrawing() const {
            return (getTotal() < 21);
        }

        void displayHand() const {
            cout << "Player: ";
            for ( auto &i : aHand ) {
                i.displayCard();
                cout << " ";
            }
            cout << "[" << getTotal() << "]" << endl;
        }
};

class ComputerPlayer : public AbstractPlayer { 
    public:
        bool isDrawing() const {
            return (getTotal() < 17);
        }

        void displayHand() const {
            cout << "Casino: ";
            for ( auto &i : aHand ) {
                i.displayCard();
                cout << " ";
            }
            cout << "[" << getTotal() << "]" << endl;
        }
};

class BlackJackGame {
    public:
        Deck m_deck;
        ComputerPlayer m_casino;
        void play() {
            cout << "Welcome to the Comp322 Blackjack table!" << endl;
            m_deck.populate();
            m_deck.shuffle();
            m_deck.deal(m_casino);

            m_casino.displayHand();

            HumanPlayer newPlayer = HumanPlayer();
            m_deck.deal(newPlayer);
            m_deck.deal(newPlayer);

            newPlayer.displayHand();
            char answer = 'y';
            while (newPlayer.isDrawing() && answer != 'n') {
                cout << "Do you want to draw? (y/n):";
                cin >> answer;

                if (answer == 'y') {
                    m_deck.deal(newPlayer);
                    newPlayer.displayHand();

                    if (newPlayer.isBusted()) {
                        cout << "Player busts." << endl;
                        cout << "Casino wins." << endl;
                        break;
                    }
                }
                else {
                    break;
                }
            }

            while (m_casino.isDrawing()) {
                if (newPlayer.isBusted()) {
                    break;
                }
                m_deck.deal(m_casino);
                m_casino.displayHand();

                if (m_casino.isBusted()) {
                    cout << "Casino busts." << endl;
                    break;
                }
            }
            if (!newPlayer.isBusted()) {
                if (m_casino.isBusted()) {
                    cout << "Player wins." << endl; 
                }

                else if (newPlayer.getTotal() > m_casino.getTotal()) {
                    cout << "Player wins." <<  endl;
                }

                else if (newPlayer.getTotal() == m_casino.getTotal()) {
                    cout << "Push: No one wins." << endl;
                }

                else if (newPlayer.getTotal() < m_casino.getTotal()) {
                    cout << "Casino wins." << endl;
                }
            }
        }
};