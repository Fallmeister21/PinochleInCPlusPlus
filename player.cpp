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
		//dont sort the suit if you dont have it :)
		if(std::find_if(sortingHand.begin(), sortingHand.end(), [&tempSuit](Card &a)
			{ return a.GetSuit() == tempSuit; }) != sortingHand.end())
		{
			auto lastSpot = std::find_if(sortingHand.rbegin(), sortingHand.rend(), [&tempSuit](Card &a)
			{ return a.GetSuit() == tempSuit; });
			auto firstSpot = std::find_if(sortingHand.begin(), sortingHand.end(), [&tempSuit](Card &a)
			{ return a.GetSuit() == tempSuit; });

			//store first and last spot for checking meld :)
			std::pair<int, int> suitRegion = std::make_pair(firstSpot->GetRank(), lastSpot->GetRank());
			suitRegions.push_back(suitRegion);

			std::sort(firstSpot, lastSpot.base(), [](Card &a, Card &b){
				return a.GetRank() < b.GetRank();
			});
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

void Player::SetMoney(int newMoney) { money = newMoney; }

void Player::SetDealer(bool newDealer) { isDealer = newDealer; }

int Player::GetScore() { return score; }

int Player::GetMoney() { return money; }

bool Player::GetDealer() { return isDealer; }

std::vector<Card> Player::GetHand() { return Hand; }

std::vector<std::pair<int,int>> Player::GetSuitRegions() { return suitRegions; }