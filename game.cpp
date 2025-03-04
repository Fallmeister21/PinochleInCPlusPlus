#include "game.h"

bool isSubsetOrEqual(std::vector<int> const& a, std::vector<int> const& b)
{
	for(auto const& av:a)
	{
		if(std::find(b.begin(),b.end(),av)!=b.end())
			continue;
		else
			return false;
	}
	return true;
}

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
	std::vector<int> baseRanksToCheck = PUtil::GetVectorofRanks(cardsToCheck);

	//look through hand
	auto regionsToCheck = player.GetSuitRegions();
	std::vector<std::string> suitList = {"Club", "Diamond", "Heart", "Spade"};

	//find meld:
	std::vector<Card> meldToCheck;
	std::vector<int> newMeldRanks;
	int potentialMeld;
	for(int i = 0; i < suitList.size(); ++i)
	{
		if(regionsToCheck[i][0] == -1 && regionsToCheck[i][1] == -1)
			continue;
		//to check just the suit i want
		std::vector<Card>::iterator firstElement = cardsToCheck.begin() + regionsToCheck[i][0];
		std::vector<Card>::iterator secondElement = cardsToCheck.begin() + regionsToCheck[i][1] + 1;
		std::vector<Card> newCardsToCheck(firstElement,secondElement);
		std::vector<int> newCardRanks = PUtil::GetVectorofRanks(newCardsToCheck);
		bool hasRun = false;
		
		potentialMeld = 0;

		//check run
		meldToCheck = CheckRun(suitList[i]);
		newMeldRanks = PUtil::GetVectorofRanks(meldToCheck);
		if(isSubsetOrEqual(newMeldRanks, newCardRanks))
		{
			hasRun = true;
			potentialMeld += 15;
		}

		//check marriages
		meldToCheck = CheckMarriage(suitList[i]);
		newMeldRanks = PUtil::GetVectorofRanks(meldToCheck);
		if(isSubsetOrEqual(newMeldRanks, newCardRanks))
		{
			//if trump is set
			if(trumpSet.second || hasRun)
				potentialMeld += 4;
			else if(!hasRun)
				potentialMeld += 2;
		}

		//check nines (only if suit is trump) -> not set yet
		if(trumpSet.second)
		{
			meldToCheck = CheckNines(suitList[i]);
			newMeldRanks = PUtil::GetVectorofRanks(meldToCheck);
			if(isSubsetOrEqual(newMeldRanks, newCardRanks))
				potentialMeld++;
		}

		//redo scores (but dont double them!) when trump is set
		player.SetSuitMeld(potentialMeld, suitList[i]);
	}
	
	potentialMeld = 0;
	//check pinochle
	meldToCheck = CheckPinochle();
	newMeldRanks = PUtil::GetVectorofRanks(meldToCheck);
	if(isSubsetOrEqual(baseRanksToCheck, newMeldRanks))
	{
		//check for double at some point
		potentialMeld += 4;
	}

	//check around
	for(int j = 11; j < 15; ++j)
	{
		meldToCheck = CheckAround(j);
		newMeldRanks = PUtil::GetVectorofRanks(meldToCheck);
		if(isSubsetOrEqual(baseRanksToCheck, newMeldRanks))
		{
			//bruh
			if(j == 11)
				potentialMeld += 4;
			else if(j == 12)
				potentialMeld += 6;
			else if(j == 13)
				potentialMeld += 8;
			else if(j == 14)
				potentialMeld += 10;
		}
	}
	player.SetSuitMeld(potentialMeld, "General");
	//dont forget to return the meld duh
	return 1;
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
std::vector<int> Game::CheckStrong(Player & player)
{
	int suitStrength = 0;
	auto regionsToCheck = player.GetSuitRegions();
	std::vector<Card> cardsToCheck = player.GetHand();
	std::vector<std::string> tempSuit = { "Club", "Diamond", "Heart", "Spade"};

	//get ranges also to only check what player has
	for(int i = 0; i < tempSuit.size(); i++)
	{
		if(regionsToCheck[i][0] == -1 && regionsToCheck[i][1] == -1)
			continue;
		for(int j = regionsToCheck[i][0]; j < regionsToCheck[i][1]; j++)
			suitStrength += cardsToCheck[i].GetRank() * 10; //idk mb something better
		player.SetSuitStrength(suitStrength, tempSuit[i]);
	}
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

void Game::SetTrump(std::string _trumpSuit)
{
	//for now :)
	trumpSet = std::make_pair(_trumpSuit,true);
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
std::vector<Card> Game::CheckRun(std::string suit)
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

std::vector<Card> Game::CheckMarriage(std::string suit)
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

std::vector<Card> Game::CheckPinochle()
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

std::vector<Card> Game::CheckAround(int checkRank)
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
std::vector<Card> Game::CheckNines(std::string suit)
{
	std::vector<Card> NinesSet;
	Card tempCard;
	tempCard.SetSuit(suit);
	tempCard.SetRank(9);
	NinesSet.push_back(tempCard);

	return NinesSet;
}