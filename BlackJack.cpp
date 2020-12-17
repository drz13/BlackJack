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
	CardValueNames valueNames;
	CardSuit suit;
	bool faceup;


	Card(CardValueNames valueNames, CardSuit suit, bool face =true) :
		valueNames(valueNames), suit(suit), faceup(face)
	{
	};

	void printCard() const
	{
		if (faceup)
		{
			cout << CardValuePrintNames[this->valueNames] << " of " << CardSuitNames[this->suit] << endl;
		}
		else
		{
			cout << "Facedown Card" << endl;;
		}
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

	Card deal(bool face=true)
	{
		Card card = this->cards.back();
		this->cards.pop_back();
		card.faceup = face;
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
	int cash;
	//int playerNumber;
	//int doubledown
	//fn split
	//fn surrender

	Hand hand;

	Player() 
		:cash(100)
	{
	}

	virtual void dealHand(Deck& deck)
	{
		hand.addCard(deck.deal());
		hand.addCard(deck.deal());
	}
	
	virtual int playRound(Deck& deck)
	{
		cout << "Hand Sum = " <<  hand.HandSum() << endl;

		bool playerFinished = false;
		int option = 0; 

		// this is actually a state machine, but i dont want to do that right now. 
		while (playerFinished != true)
		{
			cout << "Hit or Stand? " << endl;
			cout << "    1. Hit" << endl;
			cout << "    2. Stand" << endl;
			cin >> option;

			playerFinished = true;

			switch (option)
			{
				case 1: // Hit
					break;
				case 2: // Stand
					break;
				default: 
					playerFinished = false;
					cout << "Invalid Option" << endl;
			}
		}

		return 0;
	}

	int placeBet()
	{
		bool betPlaced = false;
		int betValue = 0;

		while (betPlaced == false)
		{
			cout << "Place your bet: " << endl;
			cin >> betValue; 

			if (betValue > 0 && betValue <= cash)
			{
				betPlaced = true;
			}
			else
			{
				cout << "Bet must be >0 & <= your cash" << endl;
			}
		}

		return betValue;
	}
};


class Dealer: public Player
{
public:
	Dealer()
	{

	}

	void dealHand(Deck& deck) override
	{
		hand.addCard(deck.deal());
		hand.addCard(deck.deal(true));
	}

	int playRound(Deck& deck) override
	{
		return 0;
	}
};

class Game 
{
public:
	Player player;
	Dealer dealer;
	Deck deck;

	void startGame();
	void nextNext();

	Game(int numDecks = 1)
	{
		deck = Deck(numDecks);

	}


	int round()
	{
		// 0. deal starting hands to players and dealer
		player.dealHand(deck);
		dealer.dealHand(deck);

		// 1 print values of each hand
		player.hand.printHand();
		cout << "Hand Value = " << player.hand.HandSum() << endl;
		dealer.hand.printHand();
		cout << "Hand Value = " << dealer.hand.HandSum() << endl;

		// 2. player places bet
		int playerBet = player.placeBet();
		cout << "Player Bets $" << playerBet << endl;

		// 3. player plays round
		player.playRound(deck);

		// 4. dealer plays round
		dealer.playRound(deck);

		// 5. compare hands determine winner

		// 6. report result
		return 0;
	}

	// in main loop
	// 6. player +/- points depending on outcome
	// 7. player can then start new round (keep score) or end (maybe record high score in tally)
};

int main(void)
{
	
	Game game;

	// run the round
	int roundResult = game.round();

	//updatePlayerScores(roundResult);

	return 0;

}
