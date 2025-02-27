#ifndef PCARD_H
#define PCARD_H

#include <string>

	class Card
	{
		public:
				Card();
				~Card();
				std::string GetSuit();
				int GetRank();

				void SetSuit(std::string newSuit);
				void SetRank(int newRank);
		private:
				std::string suitName;
				int rankNum;
	};
#endif