#include "player.h"

Player::Player(int playercount, int inPlayerNum)
{
	money = 0;
	score = 0;
	isDealer = false;
	playerNum = inPlayerNum;
	if(playercount == 3)
	{
		bid = 25;
		handSize = 15;
	}
	//4 player, no partners
	else
	{
		bid = 12;
		handSize = 12;
	}
}

Player::~Player() {}

void Player::AddToHand(Card newCard) { this->Hand.push_back(newCard); }

void Player::SortHand()
{
	std::vector<Card> sortingHand = this->Hand;
	//Sorted by Heart, Club, Diamond, Spade

	std::sort(sortingHand.begin(), sortingHand.end(), [](Card &a, Card &b){
		return a.GetSuit() < b.GetSuit();
	});

	//sort by rank
	std::vector<std::string> suitVector = {"Club", "Diamond", "Heart", "Spade"};
	std::string tempSuit = "";
	for(int i = 0; i < suitVector.size();i ++)
	{
		tempSuit = suitVector[i];
		std::vector<int> suitRegion;
		//dont sort the suit if you dont have it :)
		if(std::find_if(sortingHand.begin(), sortingHand.end(), [&tempSuit](Card &a)
					   { return a.GetSuit() == tempSuit; }) != sortingHand.end()   )
		{
			auto lastSpot = std::find_if(sortingHand.rbegin(), sortingHand.rend(), [&tempSuit](Card &a)
										{ return a.GetSuit() == tempSuit; });
			auto firstSpot = std::find_if(sortingHand.begin(), sortingHand.end(), [&tempSuit](Card &a)
										{ return a.GetSuit() == tempSuit; });

			std::sort(firstSpot, lastSpot.base(), [](Card &a, Card &b) { return a.GetRank() < b.GetRank(); });

			//store first and last spot for checking meld :)
			suitRegion.push_back(firstSpot - sortingHand.begin());
			suitRegion.push_back((std::distance(sortingHand.begin(), lastSpot.base())) - 1);
			suitRegions.push_back(suitRegion);
		}
		else
		{
			suitRegion.push_back(-1);
			suitRegion.push_back(-1);
			suitRegions.push_back(suitRegion);
		}
	}

	this->Hand = sortingHand;
}

void Player::ShowHand()
{
	std::cout << "Cards in hand: " << this->Hand.size() << std::endl;
	for(unsigned int i = 0; i < this->Hand.size(); i++)
		std::cout << "Hand output " << Hand[i].GetSuit() << " " << Hand[i].GetRank() << std::endl;
	std::cout << std::endl << std::endl;
}

void Player::SetScore(int newScore) { score = newScore; }

void Player::SetMeld(int inMeld) { totalMeld = inMeld; }

void Player::SetSuitMeld(int inMeld,std::string suit)
{
	std::pair<std::string,int> inMeldWSuit = std::make_pair(suit, inMeld); 
	suitMeld.push_back(inMeldWSuit); 
}

void Player::SetMoney(int newMoney) { money = newMoney; }

void Player::SetDealer(bool newDealer) { isDealer = newDealer; }

int Player::GetScore() { return score; }

int Player::GetSuitMeld(std::string suit) 
{ 
	auto suitSpot = std::find_if(suitMeld.begin(), suitMeld.end(),
				[&](const auto& pair) { return pair.first == suit; });
	return suitSpot->second;
}

int Player::GetMeld() { return totalMeld; }

int Player::GetMoney() { return money; }

bool Player::GetDealer() { return isDealer; }

std::vector<Card> Player::GetHand() { return Hand; }

std::vector<std::vector<int>> Player::GetSuitRegions() { return suitRegions; }