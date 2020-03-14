#include "blackjack.h"

class Card {
    private:
        Rank rk;    
        Type tp;
    public:
        Card (Rank rk, Type tp): rk(rk), tp(tp) {}
        ~Card() {}
        int getvalue() const {
            // for ACE - 9, values are same as assigned in enum
            // for 10, J, Q, K, they all have value 10
            return (int(rk) < 10? int(rk) : 10);
        }
        void displayCard() const {
            if(int(rk) < 10) {
                cout << int(rk); // as explained above
            } else {
                // output corresponding rank
                switch(rk){
                    case TEN:
                        cout << "10";
                        break;
                    case JACK: 
                        cout << "J";
                        break;
                    case QUEEN: 
                        cout << "Q";
                        break;
                    case KING: 
                        cout << 'K';
                        break;
                }
            }
            // output corresponding type
            switch(tp) {
                case CLUBS: 
                    cout << "C";
                    break;
                case DIAMONDS: 
                    cout << "D";
                    break;
                case HEARTS: 
                    cout << "H";
                    break;
                case SPADES: 
                    cout << "S";
                    break;
            }
        }
};

class Hand {
    private:
        vector<Card> hand;  // vector for cards in hand
    public:
        Hand() {}
        ~Hand() {}
        void add(Card cd) {    // add a card
            hand.push_back(cd);
        }
        // overloaded add method to support entry of rank and type
        void add(Rank rk, Type tp) {
            hand.push_back(Card(rk, tp));
        }
        void clear() {  // clear cards in hand
            hand.clear();
        }
        int getTotal() const {  // calculate total value
            // since this function would be used by isDrawing() method later, which is a const
            // this method must be declared const too
            int sum = 0;    // sum of points
            int aces = 0;   // number of aces in hand
            for(auto e: hand) {
                // count number of aces and score without aces
                if(e.getvalue() == 1) {
                    aces++;
                } else {
                    sum = sum + e.getvalue();
                }
            }
            // To maximize the score without busting, assume first all aces are 11 and check if busted
            // If busted: change one ace to 1 (one ace resolved) and assume rest aces are 11, go to next iteration to check
            // If not busted: then the remaining aces should be 11 to maximize score, all aces resolved
            for(int i = aces; i > 0; i--) {
                if(sum + i*11 > 21) {           // count one ace as 1
                    aces--;
                    sum = sum + 1;
                } else {                        // count one ace as 11
                    aces = 0;
                    sum = sum + i*11;
                }
            }
            return sum;
        }
        void displayHand() const {  // helper function for showing the cards in hand
            for(auto e: hand) {
                e.displayCard();
                cout << " ";
            }
        }
        int size() {    // helper function to obtain the size of current hand
            return hand.size();
        }
};

class Deck {
    private:
        vector<Card> deck;  // players obtain cards from deck
    public:
        Deck() {}
        ~Deck() {} 
        void populate() {   // Add all 52 cards to deck
            deck.clear();
            for(int tp = CLUBS; tp < SPADES; tp++) {  // iterate over each Rank
                for(int rk = ACE; rk <= KING; rk++) {  // iterate over each Type
                    // int must be used for the for-loop, but Card constructor require Rank and Type types
                    // cast to corresponding types
                    deck.push_back(Card(static_cast<Rank>(rk), static_cast<Type>(tp)));
                }
            }
        }
        void shuffle() {
            srand((unsigned)time(NULL));    // random seed to RNG depending on current time
            std::shuffle(deck.begin(), deck.end(), default_random_engine(rand())); // shuffle deck randomly
        }
        void deal(Hand &hand) {
            int n = deck.size();
            if(n > 0) {
                hand.add(deck[n-1]);  // put last card in deck to hand 
                deck.erase(deck.end()-1);  // remove card from deck
            }
        }
        void displayDeck() const { // helper function to show the deck
            for(auto e: deck) {
                e.displayCard();
                cout << " ";
            }
        }
        int size() const {  // helper function to obtain the deck size
            return deck.size();
        }
};

class AbstractPlayer: public Hand {  // abstract class not instantiable
    public: 
        virtual bool isDrawing() const = 0;  // to be implemented by derived classes
        bool isBusted() const {
            return (getTotal() > 21);
        }
};

class ComputerPlayer: public AbstractPlayer {
    public:
        ComputerPlayer() {}
        ~ComputerPlayer() {}
        bool isDrawing() const {
            return (getTotal() <= 16);  // computer must draw if they have 16 or less
        }
        void show() const {  // helper function to show computer hand
            cout << "Casino: ";
            displayHand();
            cout << "[" << getTotal() << "]" << endl;
        }
};

class HumanPlayer: public AbstractPlayer {
    public:
        HumanPlayer() {}
        ~HumanPlayer() {}
        bool isDrawing() const {  // ask for user input to draw or not
            char response;
            cout << "Do you want to draw? (y/n): ";
            cin >> response;
            while(response != 'y' && response != 'n') {  // keep asking if invalid response received
                cout << "Invalid Response ('y' or 'n' only). Do you want to draw? (y/n): ";
                cin >> response;
            }
            if(response == 'y') {
                return true;
            } else {
                return false;
            }
        }
        void announce(ComputerPlayer &computer) const {
            int computerscore = computer.getTotal();
            int playerscore = getTotal();
            // check if anyone busted
            if(playerscore > 21 && computerscore <= 21) {
                cout << "Player busts." << endl;
                cout << "Casino wins.";
                return;
            }
            if(playerscore <= 21 && computerscore > 21) {
                cout << "Computer busts." << endl;
                cout << "Player wins.";
                return;
            }
            // compare scores if both not busted
            if(playerscore <= 21 && computerscore <= 21) {
                if(computerscore == playerscore) {
                    cout << "Push. No one wins.";
                } else {
                    if(computerscore > playerscore) {
                        cout << "Casino wins.";
                    } else {
                        cout << "Player wins.";
                    }
                }
            }
            return;
        }
        void show() const {  // helper function to show player hand
            cout << "Player: ";
            displayHand();
            cout << "[" << getTotal() << "]" << endl;
        }
};

class BlackJackGame {
    public:
        BlackJackGame() {}
        ~BlackJackGame() {}
        void play() {
            // instantiate player, computer, and deck
            m_casino = ComputerPlayer();
            player = HumanPlayer();
            m_deck = Deck();
            
            // prepare deck
            m_deck.populate();
            m_deck.shuffle();
            
            // one card for casino and two for player initially
            m_deck.deal(m_casino);
            m_deck.deal(player);
            m_deck.deal(player);
            
            // show both hands
            m_casino.show();
            player.show();
            
            // ask if player wants to draw while not busted
            while(!player.isBusted()) {
                if(player.isDrawing()) {
                    m_deck.deal(player);
                    player.show();
                } else {
                    break; // stop if player decides not to draw
                }
            }
            
            // if player busts, directly loses and casino does not need to play
            if(player.isBusted()) {
                player.announce(m_casino);
                cout << endl << endl;
                return;
            }
            
            // casino's turn, draw if <= 16 and stop if exceeded or busted
            while(!m_casino.isBusted()) {
                if(m_casino.isDrawing()) {
                    m_deck.deal(m_casino);
                    m_casino.show();
                } else {
                    break;
                }
            }
            
            // show results 
            player.announce(m_casino);
            cout << endl << endl;
            
            return;
        }
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
        HumanPlayer player;
};