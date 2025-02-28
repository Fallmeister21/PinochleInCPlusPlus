#include "game.h"

Game::Game(std::vector<Player> inPlayers)
{
	GamePlayers = inPlayers;
	NewHand();
}

Game::~Game() { /* delete players vector? */ }

//check score in hand
int Game::CheckMeld(Player & player)
{
	std::vector<Card> cardsToCheck = player.GetHand();
	//look through hand
	auto regionsToCheck = player.GetSuitRegions();
	for(int i = 0; i < regionsToCheck.size(); ++i)
	{
		//find meld:
		//if run
		//if marriage
			//if trump suit marriage
		//if pinochle
			//if double
		//if aces
		//if kings
		//if queens
		//if jacks
		//if trump set
			//if any 9's in trump suit

		//add scores to find total meld
		//redo scores (but dont double them!) when trump is set
	}
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

void Game::SetTrump()
{
	//for now :)
	trumpSet = std::make_pair("None",true);
}

//used at new game instance as well
void Game::NewHand()
{
	trumpSet = std::make_pair("None",false);
}

//for meld making:
//at this point, hands are already "sorted" so checking meld here is also "sorted", so comparison can be made easily :)
//to check doubles, call twice and sort
//ex-> double_aces.pushback(checkaces) \n double_aces.pushback(checkaces) \n sort double_aces and check against suit range in hand
std::vector<Card> CheckRun(std::string suit)
{
	std::vector<Card> RunSet;
	//dont check 9's yet
	Card tempCard;
	tempCard.SetSuit(suit);
	for(unsigned int i = 2; i < 7; i++)
	{
		tempCard.SetRank(i + 8);
		RunSet.push_back(tempCard);
	}
	return RunSet;
}

std::vector<Card> CheckMarriage(std::string suit)
{
	std::vector<Card> MarriageSet;
	Card tempCard;
	tempCard.SetSuit(suit);
	tempCard.SetRank(12);
	MarriageSet.push_back(tempCard);
	tempCard.SetRank(13);
	MarriageSet.push_back(tempCard);

	return MarriageSet;
}

std::vector<Card> CheckPinochle()
{
	std::vector<Card> PinochleSet;
	Card tempCard;
	tempCard.SetSuit("Spade");
	tempCard.SetRank(12);
	PinochleSet.push_back(tempCard);
	tempCard.SetSuit("Diamond");
	tempCard.SetRank(11);
	PinochleSet.push_back(tempCard);

	return PinochleSet;
}

std::vector<Card> CheckAround(int checkRank)
{
	std::vector<Card> AroundSet;
	Card tempCard;
	std::vector<std::string> suitVec = { "Club", "Diamond", "Heart", "Spade"};
	
	//11,12,13,or14 passed in(Jack,Queen,King,Ace)
	tempCard.SetRank(checkRank);
	for(int i = 0; i < suitVec.size(); ++i)
	{
		tempCard.SetSuit(suitVec[i]);
		AroundSet.push_back(tempCard);
	}
	return AroundSet;
}

// :skull:
std::vector<Card> CheckNines(std::string suit)
{
	std::vector<Card> NinesSet;
	Card tempCard;
	tempCard.SetSuit(suit);
	tempCard.SetRank(9);
	NinesSet.push_back(tempCard);

	return NinesSet;
}