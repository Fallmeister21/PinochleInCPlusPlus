#include "game.h"

Game::Game(std::vector<Player> inPlayers)
{
	GamePlayers = inPlayers;
}

Game::~Game() { /* delete players vector? */ }

//check score in hand
int Game::CheckMeld(Player & player)
{
	//look through hand
	//for(int i = 0; i < )
	//find meld
	//add scores to find total meld
	//bidder decides trump so 9's and marriages dont get added in yet
}

//check # of cards in each suit
std::vector<int> Game::CheckSuitCount(Player & player)
{
	std::vector<Card> cardsToCheck = player.GetHand();

	std::vector<int> returnTrumps;
	int tempSuitCount = 0;
	std::vector<std::string> tempSuit = { "Club", "Diamond", "Heart", "Spade"};
	int currentSuitNum = 0;
	//club,diamond,heart,spade
	for(int i = 0; i < cardsToCheck.size(); ++i)
	{
		if(cardsToCheck[i].GetSuit() == tempSuit[currentSuitNum])
			tempSuitCount++;
		else
		{
			currentSuitNum++;
			returnTrumps.push_back(tempSuitCount);
			tempSuitCount = 0;
			if(cardsToCheck[i].GetSuit() == tempSuit[currentSuitNum])
				tempSuitCount++;
		}
	}
	returnTrumps.push_back(tempSuitCount);
	return returnTrumps;
}

//check strong cards
//Objectively -> A, 10, K, Q, J, 9
//Determine a system that will help build a strength value for each suit
std::vector<int> Game::CheckStrong(Player & player)
{

}

//calls build strength and build confidence
void Game::BuildBid(Player & player)
{

}

void Game::BuildStrength(Player & player)
{

}

void Game::BuildConfidence(Player & player)
{

}