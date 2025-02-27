#ifndef PPLAYER_H
#define PPLAYER_H

#include "card.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

	class Player
	{
		public:
			Player(int playercount, int inPlayerNum);
			~Player();
			void AddToHand(Card newCard);
			void SortHand();
			void ShowHand();
			void SetScore(int newScore);
			void SetMoney(int newMoney);
			void SetDealer(bool newDealer);
			int  GetScore();
			int  GetMoney();
			bool GetDealer();
			std::vector<Card> GetHand();
			std::vector<std::pair<int,int>> GetSuitRegions();
		private:
			int playerNum;
			std::vector<Card> Hand;
			int handSize; //differs between 3-4 players
			int score;
			int holes;
			int money;
			bool isDealer;
			//for meld
			std::vector<std::pair<int,int>> suitRegions;
			std::vector<int> suitConfidence;
			int bid;
			int handMeld;
			int handStrength;
			bool hasSaved;
			bool hasPassed;
	};

#endif