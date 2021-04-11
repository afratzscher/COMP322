//Assignment 3 COMP322
//Name: Anne-Sophie Fratzscher
//ID: 260705446

// how to compile: g++ -o a3.out assignment3.cpp
// how to run: ./a3.out

//NOTE 1: each round starts with 52 cards, meaning that, after a round, all cards are returned and shuffled 
// (ie. the probability of drawing a card in first draw is the same for every round)

//NOTE 2: numbered cards have face value (10 = 10 points, 9 = 9 points, ...),
// ace can count as 1 or 11 points (depending on other cards -> automatically picks best),
// and face card (J,Q,K) count for 10 points each

//NOTE 3: tested with valgrind for memory leak -> confirmed no memory leak
	//valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./a3.out

//NOTE 4: in case you are reading this, thank you for the great course and semester! 
         //I had a blast learning C++ :) 

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

enum Rank {ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
enum Type {CLUBS=1,DIAMONDS,HEARTS,SPADES};

class Card
{
private:
	Rank aRank; // rank of card (1, 2, 3, ... J, Q, K)
	Type aType; // suit of card (C, D, H, S)
public:
	//constructor
	Card (enum Rank pRank, enum Type pType)
	{
		// cout<<"card constructed"<<endl;
		this->aRank = pRank;
		this->aType = pType;
	}

	//destructor (default)
	~Card() 
	{
		// cout<<"card destructor"<<endl;
	}

	// returns value of card
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
	// NOTE: ace outputted as "1" instead of "A"
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
	std::vector<Card> aHand; // vector holding cards
public:
	//constructor (default)
	Hand() 
	{
		// cout<<"hand constructor"<<endl;
	}
	
	// destructor (default)
	virtual ~Hand()
	{
		// cout<<"hand destructor"<<endl;
	}

	//add card to hand
	void add(Card pCard)
	{
		aHand.push_back(pCard);
	}

	//clear (empty hand)
	void clear()
	{
		aHand.clear(); // clear is built-in function for vector
	}

	//get total numerical value of all cards in hand
	int getTotal() const
	{
		int sum = 0; // allows returning 0 if empty hand...

		//sum everything first (assuming ace = 1)
		for(int i = 0; i < aHand.size(); i++)
		{
			Card temp = aHand[i];
			sum += temp.getValue();
		}

		//repeat for aces (decide if ace = 1 or 11)
		for(int i = 0; i < aHand.size(); i++)
		{
			Card temp = aHand[i];
			if (temp.getValue() == 1)
			{
				if(sum <=11) // if adding leads to < 21, ace is 11 (do +10 b/c already did +1 earlier)
				{
					sum+=10;
				} 
				// otherwise, dont do anything
			}
		}
		return sum;
	}

	// print hand using <<
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
	//constructor (default)
	Deck()
	{
		// cout<<"deck constructor"<<endl;
	}

	//destructor (default)
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

	//shuffles deck using rand
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

	//deals ONE card from the deck
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
	//constructor (default)
	AbstractPlayer() 
	{
		// cout<<"constructor abstract"<<endl;
	};

	//destructor (default)
	virtual ~AbstractPlayer()
	{
		// cout<<"destructor abstract"<<endl;
	}

	//indicates if player wants to draw new card (T/F)
	//NOTE: Pure virtual method, so means derived classes MUST implement this function!
	virtual bool isDrawing() const = 0;

	//returns if busted or not (T if sum <=21, F if >21)
	virtual bool isBusted()
	{
		return aHand.getTotal() > 21;
	}
};


class ComputerPlayer: public AbstractPlayer
{
public:
	//constructor (default)
	ComputerPlayer()
	{
		// cout<<"Computer constructor"<<endl;
	}

	//destructor (default)
	~ComputerPlayer()
	{
		// cout<<"Computer destructor"<<endl;
	}

	// check if is drawing (T if sum <=16, F if sum > 16)
	bool isDrawing() const
	{
		if(aHand.getTotal() <= 16)
		{
			return true;
		} 
		return false;
	}

	//get total for computer
	int getTotal()
	{
		return aHand.getTotal(); // calls getTotal() method in Hand class
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
	//constructor (default)
	HumanPlayer()
	{
		// cout<<"Human constructor"<<endl;
	}

	//destructor (default)
	~HumanPlayer()
	{
		// cout<<"Human destructor"<<endl;
	}

	//checks if want to continue drawing... 
	bool isDrawing() const 
	{
		char answer; 
		while(true)
		{
			cout<<"Do you want to draw? (y/n): ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				return true;
			}
			else if (answer == 'n' || answer == 'N')
			{
				return false;
			}
			else
			{
				cout<<"Invalid input. Please try again."<<endl;
				cin.clear();
				fflush(stdin);
				//loops until either returns true or false...
			}
		}
	}

	//announces who won and why (if bust or push)
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
	//constructor (default)
	BlackJackGame()
	{
		// cout<<"BJ const"<<endl;
	} 

	// destructor (default)
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
		m_deck.deal(m_casino.getHand()); // ADD BACK
		cout<<m_casino;

		// 2 cards for player
		m_deck.deal(m_client.getHand()); //ADD BACK
		m_deck.deal(m_client.getHand());//ADD BACK
		cout<<m_client;

		//ask if want to draw
		char answer = 'y';
		bool busted = false;
		int i = 0;

		// let player draw as long as they want (OR until they hit 21, because then they cannot get better)
		while (m_client.isDrawing())
		{
			m_deck.deal(m_client.getHand()); 
			cout<<m_client;

			// if drawing leads to bust, stop drawing and end game...
			if (m_client.isBusted())
			{
				m_client.announce(m_casino);
				busted = true;
				break;
			}
			if (m_client.getHand().getTotal() == 21) // if have exactly 21, let casino draw
			{
				break;
			}
		}
		//then let computer draw (if player didnt bust) as long as capable (as long <= 16)
		if (!busted)
		{	
			int i = 0;
			cout<<"Casino drawing..."<<endl;
			while(m_casino.isDrawing() && !m_casino.isBusted())
			{
				m_deck.deal(m_casino.getHand()); // addback
				cout<<m_casino;
			}
			m_client.announce(m_casino);
			return;
		}		
	}
};

int main()
{
	cout << "\tWelcome to the COMP322 Blackjack game!" << endl << endl;
	BlackJackGame game;

	// the main loop of the game
	bool playAgain = true;
	char answer = 'y';
	while (playAgain)
	{
		game.play();

		// Check whether the player would like to play another round
		cout<<"----------------"<<endl;
		playAgain = false;
		bool invalidAnswer = true;
		while(invalidAnswer)
		{
			cout << "Would you like another round? (y/n): ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				playAgain = true;
				invalidAnswer = false;
			}
			else if (answer == 'n' || answer == 'N')
			{
				playAgain = false;
				invalidAnswer = false;
			}
			else
			{
				cout<<"Invalid input. Please try again."<<endl;
				cin.clear();
				fflush(stdin);
				//loops until either returns true or false...
			}
		}
	}

	cout<<"Game over!"<<endl;
	return 0;
}