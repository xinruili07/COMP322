#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "blackjack.h"

using namespace std;

Card::Card(Rank pRank, Type pType) {
    aRank = pRank;
    aType = pType;
}
int Card::getValue() const {
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
void Card::displayCard() const{
    switch(aType) {
        case CLUBS:
            if (aRank == JACK) {
                cout << "J" << "C";
                break;
            }
            if (aRank == QUEEN) {
                cout << "Q" << "C";
                break;
            }

            if (aRank == KING) {
                cout << "K" << "C";
                break;
            }
            cout << getValue() << "C";
            break;
            

        case DIAMONDS:
            if (aRank == JACK) {
                cout << "J" << "D";
                break;
            }
            if (aRank == QUEEN) {
                cout << "Q" << "D";
                break;
            }

            if (aRank == KING) {
                cout << "K" << "D";
                break;
            }
            cout << getValue() << "D";
            break;
            

        case HEARTS:
            if (aRank == JACK) {
                cout << "J" << "H";
                break;
            }
            if (aRank == QUEEN) {
                cout << "Q" << "H";
                break;
            }

            if (aRank == KING) {
                cout << "K" << "H";
                break;
            }
            cout << getValue() << "H";
            break;
            

        case SPADES:
            if (aRank == JACK) {
                cout << "J" << "S";
                break;
            }
            if (aRank == QUEEN) {
                cout << "Q" << "S";
                break;
            }

            if (aRank == KING) {
                cout << "K" << "S";
                break;
            }
            cout << getValue() << "S";
            break;
            
    }
}


void Hand::add(Card card) {
    aHand.push_back(card);
}

void Hand::clear() {
    aHand.clear();
}

void Hand::displayHand() const {
    for(int i=0; i<aHand.size(); ++i) {
        aHand[i].displayCard();
        cout << " ";
    }
}

int Hand::getTotal() const {
    bool ace = false;
    int sum = 0;
    for (int i=0; i<aHand.size(); ++i) {
        if (aHand[i].getValue() == 1) {
            ace = true;
        }
        sum += aHand[i].getValue();
    }

    if (ace && sum + 10 <= 21) {
        return sum + 10;
    }
    else {
        return sum;
    }
}

void Deck::populate() {
    aDeck.clear();
    int aRank, aType;
    for (aType = CLUBS; aType <= SPADES; aType++) {
        for (aRank = ACE; aRank <= KING; aRank++) {
            Card card = Card(Rank(aRank), Type(aType));
            aDeck.push_back(card);
        }
    }
}

void Deck::shuffle() {
    random_shuffle(aDeck.begin(), aDeck.end());
}

void Deck::deal(Hand &pHand) {
    Card card = aDeck.back();
    aDeck.pop_back();
    pHand.add(card);
}

bool AbstractPlayer::isBusted() {
    return getTotal() > 21;
}


HumanPlayer::HumanPlayer() {}
bool HumanPlayer::isDrawing() const {
    return (getTotal() < 21);
}

void HumanPlayer::displayPlayer() const {
    cout << "Player: ";
    displayHand();
    cout << "[" << getTotal() << "]" << endl;
}

bool ComputerPlayer::isDrawing() const {
    return (getTotal() < 17);
}

void ComputerPlayer::displayPlayer() const {
    cout << "Casino: ";
    displayHand();
    cout << "[" << getTotal() << "]" << endl;
}

void BlackJackGame::play() {
    cout << "Welcome to the Comp322 Blackjack table!" << endl;
    m_deck.populate();
    m_deck.shuffle();
    m_deck.deal(m_casino);

    m_casino.displayPlayer();

    HumanPlayer newPlayer = HumanPlayer();
    m_deck.deal(newPlayer);
    m_deck.deal(newPlayer);

    newPlayer.displayPlayer();
    char answer = 'y';
    while (newPlayer.isDrawing() && answer != 'n') {
        cout << "Do you want to draw? (y/n):";
        cin >> answer;

        if (answer == 'y') {
            m_deck.deal(newPlayer);
            newPlayer.displayPlayer();

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
        m_casino.displayPlayer();

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

    m_casino.clear();
    
}