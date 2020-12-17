// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <array>

using namespace std;

enum CardValueNames
{
	Ace, 
	Two, 
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};
 
array<string, 13> CardValuePrintNames = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10","Jack", "Queen", "King"};
array<int, 13> CardValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

enum CardSuit
{
	Hearts,
	Spade,
	Club,
	Diamond
};

array<string,4> CardSuitNames = { "Hearts", "Spades", "Clubs", "Diamonds"};

struct Card
{
public:
	bool faceup;
	CardValueNames valueNames;
	CardSuit suit;


	Card(CardValueNames valueNames, CardSuit suit) :
		valueNames(valueNames), suit(suit)
	{
	};

	void printCard() const
	{
		cout << CardValuePrintNames[this->valueNames] << " of " << CardSuitNames[this->suit] << endl;
	}
};

class Deck
{
public:
	vector <Card> cards;
	
	void shuffle()
	{
		random_shuffle(this->cards.begin(), this->cards.end());
	}

	Deck(int numDecks=1)
	{
		int k = 0;
		for (int count =0; count < numDecks; count++)
		{
			for (int values = 0; values < 13; values++)
			{
				for (int suits = 0; suits < 4; suits++)
				{
					cards.push_back(Card((CardValueNames)values, (CardSuit)suits));
					k++;
				}
			}
		}
	
		//shuffle();
	}

	Card deal()
	{
		Card card = this->cards.back();
		this->cards.pop_back();
		return card;
	}

	void printDeck()
	{
		for (const auto& card : this->cards)
		{
			card.printCard();
		}
	}
};

class Hand
{
public :
	vector <Card> cards;

	void addCard(Card card)
	{
		cards.push_back(card);
	}

	int HandSum()
	{
		int sum = 0;

		for (const auto& card : cards)
		{
			sum += CardValues[card.valueNames];
		}

		return sum;
	};

	Hand()
	{

	}

	void printHand()
	{
		for (const auto& card : cards)
		{
			card.printCard();
		}
	}
};


class Player
{	
public:
	int hit();
	void stand();
	int points;
	//int doubledown
	//fn split
	//fn surrender

	Hand hand;

	Player() 
		:dollars(100)
	{

	}
};


class Dealer: public Player
{
public:
	Dealer()
	{

	}
};

class Game 
{
public:
	vector<Player>& players;
	Dealer dealer;
	Deck deck;

	void startGame();
	void nextNext();

	Game(vector<Player>& p, int numDecks = 1)
		: players(p)
	{
		deck = Deck(numDecks);


	}

	// round
	// 0. deal two cards to each player
	// 0.1 print the faceup values of the respective hands
	// 1. iterate through player vector, have players do their round
	//	1.0 calculate player hand -> bust or go on
	//	1.1 player places bet
	//	1.2 player given options -> if pass go to 2
	//  1.3 return to 1.0 
	// 2. dealer does their thing (dealer.doRound())
	//	2.1 dealer hits until bust or >=17
	// 3. print all player scores/busts
	// 4. determine winner/tie ("push")
	// 5. player +/- points depending on outcome
	// 6. player can then start new round (keep score) or end (maybe record high score in tally)
};

int main(void)
{
	// init player and dealer hands
	Deck gameDeck(2);
	
	gameDeck.printDeck();
	cout << "deck size = " << gameDeck.cards.size() << endl;

	Hand hand1;

	hand1.addCard(gameDeck.deal());
	
	cout << "Hand 1 = "; 
	hand1.printHand();

	cout << "Hand 1 sum = " << hand1.HandSum();


	return 0;

}
