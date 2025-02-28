#ifndef PGAME_H
#define PGAME_H

#include <vector>
#include <string>
#include "player.h"

	class Game
	{
		public:
			Game(std::vector<Player> inPlayers);
			~Game();
			//check score in hand
			int CheckMeld(Player & player);
			//check # of cards in each suit
			std::vector<int> CheckSuitCount(Player & player);
			//check strong cards
			std::vector<int> CheckStrong(Player & player);
			//calls build strength and build confidence
			void BuildBid(Player & player);
			void BuildStrength(Player & player);
			void BuildConfidence(Player & player);
			void SetTrump();
			//used at new game instance as well
			void NewHand();
		private:
			std::vector<Player> GamePlayers;
			std::string currentTrump;
			int gamePrice;
			int holePrice;
			std::pair<std::string, bool> trumpSet;
			
	};

#endif