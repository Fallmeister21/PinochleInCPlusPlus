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
			void SetMeld(int inMeld);
			void SetSuitMeld(int inMeld, std::string suit);
			void SetSuitStrength(int inStrength, std::string suit);
			void SetSuitConfidence(int inConfidence, std::string suit);
			void SetMoney(int newMoney);
			void SetDealer(bool newDealer);
			int  GetScore();
			int  GetMeld();
			int  GetSuitMeld(std::string suit);
			int  GetMoney();
			bool GetDealer();
			std::vector<Card> GetHand();
			std::vector<std::vector<int>> GetSuitRegions();
		private:
			int playerNum;
			std::vector<Card> Hand;
			int handSize; //differs between 3-4 players
			int score;
			int totalMeld;
			std::vector<std::pair<std::string,int>> suitMeld;
			int holes;
			int money;
			bool isDealer;
			//for meld
			std::vector<std::vector<int>> suitRegions;
			std::vector<std::pair<std::string,int>> suitConfidence;
			std::vector<std::pair<std::string,int>> suitStrength;
			int bid;
			int handMeld;
			int handStrength;
			bool hasSaved;
			bool hasPassed;
	};

#endif