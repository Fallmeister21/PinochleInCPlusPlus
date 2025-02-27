#include "card.h"

Card::Card()
{
	suitName = "";
	rankNum = 0;
}

Card::~Card() { /*dont have to do anything to destroy it :)*/ }

std::string Card::GetSuit() { return suitName; }

int Card::GetRank() { return rankNum; }

void Card::SetSuit(std::string newSuit) { suitName = newSuit; }

void Card::SetRank(int newRank) { rankNum = newRank; }