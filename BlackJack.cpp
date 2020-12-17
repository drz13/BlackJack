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
	//int doubledown
	//fn split
	//fn surrender

	Hand hand;
};


class Dealer: public Player
{

};

class Game 
{
	vector<Player> players;
	Deck gameDeck;
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
