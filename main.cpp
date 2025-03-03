#include "player.h"
#include "card.h"
#include "deck.h"
#include "util.h"
#include "game.h"
#include <vector>
#include <string>

int main()
{
	Deck mainDeck = Deck();
	std::vector<Player> Players;
	

	for(unsigned int i = 0; i < 3; i++)
		Players.push_back(Player(3, i));
	Game CurrentGame = Game(Players);
	//Dealer is player 1 to start
	//figure out a randomizer to start -> different methods?
	Players[0].SetDealer(true);

	//the magic number technically 7 but lets double it :eyes:
	for(unsigned int i = 0; i < 14; i++)
		mainDeck.ShuffleDeck(mainDeck.CheckDeckList());
	mainDeck.DealToKitty();

	if(Players.size() == 3)
		mainDeck.DealThreeHandDeck(mainDeck.CheckDeckList(), Players);

	//testing shhhhhhh
	std::vector<std::vector<int>> playersSuitCounts;
	for(unsigned int i = 0; i < Players.size(); i++)
	{
		Players[i].SortHand();
		Players[i].ShowHand();
		playersSuitCounts.push_back(CurrentGame.CheckSuitCount(Players[i]));
		std::cout << "Meld for player " << i << "\n";
		CurrentGame.CheckMeld(Players[i]);
		std::cout << "\n\n\n";
	}

	for(unsigned int i = 0; i < playersSuitCounts.size(); i++)
	{
		std::cout << "Counts for player " << i << ": Club,Diamond,Heart,Spade" << std::endl;
		for(int j = 0; j < playersSuitCounts[i].size(); j++)
			std::cout << playersSuitCounts[i][j] << " ";
		std::cout << std::endl << std::endl;
	}

	//to compare
	//dont really care about deck anymore. it still exists so it can be used for next hand but as of right now it's irrelevant
	//also kitty is technically "hidden". nobody knows whats in it until bid is set.
	//mainDeck.OutputDeckList();
	mainDeck.OutputKitty();

	return 0;
}