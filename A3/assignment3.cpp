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
	int getTotal()
	{
		int sum = 0; // allows returning 0 if empty hand...
		for(int i = 0; i < aHand.size(); i++){
			// need to account for if want ace to be 1 or 11
			if (aHand[i].getValue() == 1)
			{
				if(sum <=10) // if adding leads to < 21, add 11
				{
					sum+=11;
				}
				else // if adding leads to >21, add 1
				{	
					sum+=1;
				}
			}
			else // if NOT ace, just add value
			{
				sum += aHand[i].getValue();
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

};

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

int main(){
// {
// 	Card test = Card(Rank(TWO), Type(DIAMONDS));
// 	Card test2 = Card(Rank(ACE), Type(DIAMONDS));
// 	// cout<<test;
// 	test.displayCard();
// 	cout<<endl;
	Hand newHand = Hand();
	cout<<"hand SIZE: "<<newHand.size()<<endl;
	Deck newDeck = Deck();
	newDeck.populate();
	newDeck.size();
	newDeck.shuffle();
	cout<<"deck SIZE: "<<newDeck.size()<<endl;
	newHand.view();
	cout<<"here"<<endl;
	newDeck.deal(newHand);
	newHand.view();
	cout<<endl;
	newDeck.deal(newHand);
	newHand.view();
	cout<<endl;
	cout<<newDeck.size();

	// newHand.size();
	// cout<<"Total: "<<newHand.getTotal()<<endl;



	// cout<<"here"<<endl;

	// for (inti = Type::CLUBS, i<=Type::SPADES;i++)
	// {
	// 	for (int j = Rank::ACE; j<=Rank::KING; j++)
	// 	{
	// 		Card test = 
	// 	}
	// }
	// , Type DIAMOND);
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