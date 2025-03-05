#ifndef PDECK_H
#define PDECK_H

#include "card.h"
#include "player.h"

#include <vector>
#include <unordered_map>

	//also acts as a dealer/reporter
	//arguably, the deck shouldnt know what the counts are as that should be left to the player
	//but this will eventually be used for logging to see stats on how the other players played as well
	class Deck
	{
		public:
			Deck();
			void OutputDeckList();
			void OutputKitty();
			//uses a version of the fisher yates shuffle since i dont think random shuffle exists for unordered maps
			void ShuffleDeck(std::unordered_map<int, Card> oldDeckList);
			void DealThreeHandDeck(std::unordered_map<int, Card> deckList, std::vector<Player> & players);
			void DealFourHandDeck(std::unordered_map<int, Card> deckList, std::vector<Player> players);
			void DealToKitty();
			std::unordered_map<int, Card> CheckDeckList();

			int  GetCards();
			int  GetSuits();
			int  GetRanks();
			void SetCards(int newCardCount);
			void SetSuits(int newSuitCount);
			void SetRanks(int newRankCount);
		private:
			//position + card
			std::unordered_map<int, Card> Cards;
			std::vector<std::pair<int, Card>> Kitty;
			std::vector<int> kittySpots;
			//score related
			int scoreGoal;
			int gameCost;
			int holeCost;
			int bidAmount;
			//advanced params
			int cardCount; //cards left in deck
			int suitCount; //number of cards per suit left
			int rankCount; //number of cards per rank left
	};

#endif