#include "util.h"

std::vector<int> PUtil::GetVectorofRanks(std::vector<Card> inCards)
{
	std::vector<int> returnRanks;

	for(int i = 0; i < inCards.size(); ++i)
		returnRanks.push_back(inCards[i].GetRank());

	return returnRanks;
}