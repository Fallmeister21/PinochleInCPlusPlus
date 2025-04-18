#include "card.h"
#include "deck.h"
#include "game.h"
#include "player.h"
#include "util.h"

#include <iostream>
#include <string>
#include <vector>

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

	for(unsigned int i = 0; i < Players.size(); i++)
	{
		Players[i].SortHand();
		Players[i].ShowHand();
		CurrentGame.CheckMeld(Players[i]);
	}

	std::vector<std::string> suitVector = {"Club", "Diamond", "Heart", "Spade", "General"};
	for(unsigned int i = 0; i < Players.size(); i++)
	{
		std::cout << "Checking player " << i << "'s meld\n";
		for(unsigned int j = 0; j < suitVector.size(); j++)
			std::cout << "Meld for suit: " << suitVector[j] << " " << Players[i].GetSuitMeld(suitVector[j]) << "\n";
		std::cout << "\n";
	}

	//to compare
	//dont really care about deck anymore. it still exists so it can be used for next hand but as of right now it's irrelevant
	//also kitty is technically "hidden". nobody knows whats in it until bid is set.
	//mainDeck.OutputDeckList();
	mainDeck.OutputKitty();

	return 0;
}