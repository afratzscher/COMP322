//Assignment 3 COMP322
//Name: Anne-Sophie Fratzscher
//ID: 260705446

// how to compile: g++ -o a3.out assignment3.cpp
// how to run: ./a3.out

//NOTE: tested with valgrind for memory leak -> confirmed no memory leak

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

enum Rank {ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
enum Type {CLUBS=1,DIAMONDS,HEARTS,SPADES};

class Card
{
private:
	Rank aRank;
	Type aType;
public:
	//constructor
	Card (enum Rank pRank, enum Type pType)
	{
		// cout<<"card constructed"<<endl;
		this->aRank = pRank;
		this->aType = pType;
	}
	//destructor
	~Card()
	{
		// cout<<"card destructor"<<endl;
	}
	// returns value
	int getValue(){
		if (aRank<=10){
			return aRank; // for # cards
		}
		else{
			return 10; // for face cards
		}
	}
	//display card using overloaded << operator
	void displayCard(){
		cout<<(*this);
	}

	friend ostream& operator<<(ostream& os, const Card& pCard); 
};

// prints card rank and suit using "<<"
ostream& operator<<(ostream& os, const Card& pCard)
{
	// outputs card value
	if(pCard.aRank <= 10)
		os<<pCard.aRank;
	else if (pCard.aRank == 11)
		os<<"J";
	else if (pCard.aRank == 12)
		os<<"Q";
	else
		os<<"K";

	// outputs card suit
	if (pCard.aType == 1)
		os<<"C";
	else if (pCard.aType == 2)
		os<<"D";
	else if (pCard.aType == 3)
		os<<"H";
	else
		os<<"S";
	return os;
}

class Hand
{
protected:
	std::vector<Card> aHand;
public:
	//constructor
	Hand() 
	{
		// cout<<"hand constructor"<<endl;
	}
	// destructor
	virtual ~Hand()
	{
		// cout<<"hand destructor"<<endl;
	}
	//add card
	void add(Card pCard)
	{
		aHand.push_back(pCard);
	}
	//clear 
	void clear()
	{
		aHand.clear(); // built-in function for vector
	}
	//size of hand
	int size()
	{
		return aHand.size();
	}
	//get total numerical values
	int getTotal() const
	{
		int sum = 0; // allows returning 0 if empty hand...

		//sum first (assuming ace = 1)
		for(int i = 0; i < aHand.size(); i++)
		{
			Card temp = aHand[i];
			sum += temp.getValue();
		}

		//repeat for ace
		for(int i = 0; i < aHand.size(); i++)
		{
			Card temp = aHand[i];
			if (temp.getValue() == 1)
			{
				if(sum <=11) // if adding leads to < 21, add 11 (do +10 b/c already did +1 earlier)
				{
					sum+=10;
				}
			}
		}
		return sum;
	}

	// view hand
	void view()
	{
		for(int i = 0; i < aHand.size(); i++){
			aHand[i].displayCard();
			cout<<" ";
		}
	}

	// print hand
	friend ostream& operator<<(ostream& os, const Hand& pHand); 
};


// prints hand using"<<"
ostream& operator<<(ostream& os, const Hand& pHand)
{
	for (int i = 0; i < pHand.aHand.size(); i++)
	{
		Card temp = pHand.aHand[i];
		os<<temp<<" ";

	}
	return os;
}

class Deck: public Hand
{
public:
	//constructor
	Deck()
	{
		// cout<<"deck constructor"<<endl;
	}

	//destructor
	~Deck()
	{
		// cout<<"Deck destructor"<<endl;
	}

	//populate deck with 52 standard cards
	void populate()
	{
		Card test = Card(Rank(TWO), Type(DIAMONDS));
		for (int i = ACE; i <= KING; i++)
		{
			for (int j = CLUBS; j <= SPADES; j++)
			{
				this->add(Card(Rank(i), Type(j)));
			}
		}
	}

	//shuffles deck
	void shuffle()
	{
		srand(time(NULL));
		std::vector<Card> temp = aHand;
		this->clear();
		while(temp.size() > 0)
		{
			int idx = rand() % temp.size();
			this->add(temp[idx]);
			temp.erase(temp.begin() + idx);
		}
	}

	//deals a card from the deck
	void deal(Hand& pHand)
	{
		pHand.add(this->aHand.back()); // access last element in vector
		this->aHand.pop_back(); // pops last element
	}
};

class AbstractPlayer
{
protected:
	Hand aHand;
public:
	//constructor
	AbstractPlayer() 
	{
		// cout<<"constructor abstract"<<endl;
	};

	//destructor
	virtual ~AbstractPlayer()
	{
		// cout<<"destructor abstract"<<endl;
	}

	//indicates if player wants to draw new card (T?F)
	virtual bool isDrawing() const = 0;

	//returns if busted or not (T/F)
	virtual bool isBusted()
	{
		return aHand.getTotal() > 21;
	}
};


class ComputerPlayer: public AbstractPlayer
{
public:
	//constructor
	ComputerPlayer()
	{
		// cout<<"Computer constructor"<<endl;
	}

	//destructor
	~ComputerPlayer()
	{
		// cout<<"Computer destructor"<<endl;
	}

	// check if is drawing TO DO
	bool isDrawing() const
	{
		cout<<"is drawing"<<endl;
		return true;
	}

	//get total for computer
	int getTotal()
	{
		return aHand.getTotal();
	}

	//get hand (for drawing)
	Hand& getHand()
	{
		return aHand;
	}

	friend ostream& operator<<(ostream& os, const ComputerPlayer &pComputer); 
};

// print casino hand + total value using "<<"
ostream& operator<<(ostream& os, const ComputerPlayer &pComputer)
{
	os<<"Casino: ";
	os<<pComputer.aHand;
	os<<"["<<pComputer.aHand.getTotal()<<"]"<<endl;
	return os;
}

class HumanPlayer: public AbstractPlayer
{
public:
	//constructor
	HumanPlayer()
	{
		// cout<<"Human constructor"<<endl;
	}

	//destructor
	~HumanPlayer()
	{
		// cout<<"Human destructor"<<endl;
	}

	//checks if want to continue drawing... 
	bool isDrawing() const  // TO DO
	{
		return true;
	}

	//announce
	void announce(ComputerPlayer pPlayer)
	{
		if (this->isBusted()) // casino wins b/c player busts
			cout<<"Player busts."<<endl<<"Casino wins."<<endl;
		else if (pPlayer.isBusted()) // player wins b/c casino busts
			cout<<"Casino busts."<<endl<<"Player wins."<<endl;
		else if (pPlayer.getTotal() == aHand.getTotal()) // same score, so push
			cout<<"Push: No one wins."<<endl;
		else if (pPlayer.getTotal() > aHand.getTotal()) // casino > player
			cout<<"Casino wins."<<endl; 
		else if (pPlayer.getTotal() < aHand.getTotal()) // casino < player
			cout<<"Player wins."<<endl;
	}

	//get hand (for drawing)
	Hand& getHand()
	{
		return aHand;
	}

	friend ostream& operator<<(ostream& os, const HumanPlayer &pHuman);
};

// print Human player hand + total value using "<<"
ostream& operator<<(ostream& os, const  HumanPlayer &pHuman)
{
	os<<"Player: ";
	os<<pHuman.aHand;
	os<<"["<<pHuman.aHand.getTotal()<<"]"<<endl;
	return os;
}

class BlackJackGame
{
private:
	Deck m_deck;
	ComputerPlayer m_casino;
	HumanPlayer m_client;
public:
	//constructor
	BlackJackGame()
	{
		// cout<<"BJ const"<<endl;
	}
	~BlackJackGame()
	{
		// cout<<"BJ destruct"<<endl;
	}

	//initializes each round
	void initialize()
	{
		// initialize -> creates human player, computer player, shuffled deck
		m_client = HumanPlayer();
		m_casino = ComputerPlayer();
		m_deck = Deck();
		m_deck.populate();
		m_deck.shuffle();
	}

	// plays a round
	void play()
	{
		initialize();
		// 1 card for casino
		m_casino.getHand().add(Card(Rank(QUEEN), Type(SPADES)));
		// m_deck.deal(m_casino.getHand());
		cout<<m_casino;

		// 2 cards for player
		m_client.getHand().add(Card(Rank(FOUR), Type(CLUBS)));
		m_client.getHand().add(Card(Rank(FOUR), Type(HEARTS)));
		// m_deck.deal(m_client.getHand());
		// m_deck.deal(m_client.getHand());
		cout<<m_client;

		//ask if want to draw
		char answer = 'y';
		bool toDraw = true;
		bool busted = false;
		int i = 0;

		// let player draw as long as they want
		while (toDraw)
		{
			cout<<"Do you want to draw? (y/n): ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				if(i == 0)
					m_client.getHand().add(Card(Rank(THREE), Type(SPADES)));
				else if (i==1)
					m_client.getHand().add(Card(Rank(JACK), Type(CLUBS)));
				else if (i==2)
					m_client.getHand().add(Card(Rank(FOUR), Type(HEARTS)));
				// m_deck.deal(m_client.getHand());
				cout<<m_client;
				i++;
				// if drawing leads to bust, stop drawing and end game...
				if (m_client.isBusted())
				{
					m_client.announce(m_casino);
					toDraw = false;
					busted = true;
				}
				if (m_client.getHand().getTotal() == 21) // if have exactly 21, let casino draw
				{
					toDraw = false;
				}
			}
			else if (answer == 'n' || answer == 'N')
			{
				toDraw = false;
			}
			else // account for mistake
			{
				cout<<"Invalid input. Please try again."<<endl;
				cin.clear();
				fflush(stdin);
			}
		}
		//then let computer draw (if player didnt bust) as long as capable (as long <= 16)
		if (!busted)
		{	
			int i = 0;
			cout<<"Casino drawing..."<<endl;
			while(!m_casino.isBusted() && m_casino.getHand().getTotal() <= 16)
			{
				if (i==0)
					m_casino.getHand().add(Card(Rank(ACE), Type(HEARTS)));
				else if (i==1)
					m_casino.getHand().add(Card(Rank(THREE), Type(SPADES)));
				else if (i==2)
					m_casino.getHand().add(Card(Rank(KING), Type(SPADES)));
				// m_deck.deal(m_casino.getHand());
				cout<<m_casino;
				i++;
			}
			m_client.announce(m_casino);
		}		
	}
};

int main()
{
	BlackJackGame game = BlackJackGame();
	game.play();
// 	Card test = Card(Rank(TWO), Type(DIAMONDS));
// 	Card test2 = Card(Rank(ACE), Type(DIAMONDS));
// 	// cout<<test;
// 	test.displayCard();
// 	cout<<endl;
	// Hand newHand = Hand();
	// cout<<"hand SIZE: "<<newHand.size()<<endl;
	// Deck newDeck = Deck();
	// newDeck.populate();
	// newDeck.size();
	// newDeck.shuffle();
	// cout<<"deck SIZE: "<<newDeck.size()<<endl;
	// newHand.view();
	// cout<<"here"<<endl;
	// newDeck.deal(newHand);
	// newHand.view();
	// cout<<endl;
	// newDeck.deal(newHand);
	// newHand.view();
	// cout<<endl;
	// cout<<newDeck.size();

	// ComputerPlayer comp = ComputerPlayer();
	// HumanPlayer hum = HumanPlayer();
	// Deck newDeck = Deck();
	// newDeck.populate();
	// newDeck.shuffle();
	// cout<<newDeck.size()<<endl;
	// newDeck.deal(comp.getHand());
	// cout<<newDeck.size()<<endl;
	// comp.getHand().view();
	// cout<<comp.getTotal();
	// cout<<endl;
	// newDeck.deal(comp.getHand());
	// cout<<newDeck.size()<<endl;
	// comp.getHand().view();
	// cout<<comp.getTotal();
	// cout<<endl;
	// hum.announce(comp);


	// cout << "\tWelcome to the COMP322 Blackjack game!" << endl << endl;
	// BlackJackGame game;

	// // the main loop of the game
	// bool playAgain = true;
	// char answer = 'y';
	// while (playAgain)
	// {
	// 	game.play();

	// 	// Check whether the player would like to play another round
	// 	cout << "Would you like another round? (y/n): ";
	// 	cin >> answer;
	// 	cout << endl << endl;
	// 	playAgain = (answer == 'y' ? true : false);
	// }

	// cout << "Game over!";
	// return 0;
}