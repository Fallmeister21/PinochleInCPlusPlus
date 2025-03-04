#include "deck.h"

Deck::Deck()
{
	int numDecks = 1;
	int deckSize = 48;

	Card tempCard = Card();
	int deckCount = 1;
	//for each suit
	for(unsigned int i = 0; i < 4; i++)
	{
		//for each rank
		//9 - 13 :)
		for(unsigned int j = 1; j < 7; j++)
		{
			if(i == 0)
				tempCard.SetSuit("Heart");
			else if(i == 1)
				tempCard.SetSuit("Diamond");
			else if(i == 2)
				tempCard.SetSuit("Club");
			else if(i == 3)
				tempCard.SetSuit("Spade");
			tempCard.SetRank(j + 8);
			//2 of each rank in each suit
			Cards.insert({deckCount, tempCard});
			deckCount++;
			//std::cout << tempCard.GetSuit() << " " << tempCard.GetRank() << std::endl;
			Cards.insert({deckCount, tempCard});
			deckCount++;
		}
	}
}

void Deck::OutputDeckList()
{
	for(std::unordered_map<int,Card>::iterator it = this->Cards.begin();
	    it != this->Cards.end(); ++it)
		std::cout << " " << it->second.GetRank() << " " << it->second.GetSuit() << "\n";
	return;
}

void Deck::OutputKitty()
{
	for(std::vector<std::pair<int,Card>>::iterator it = this->Kitty.begin();
	    it != this->Kitty.end(); ++it)
	{
		std::pair<int,Card> currentPair = *it;
		std::cout << currentPair.second.GetRank() << " " << currentPair.second.GetSuit() << "\n";
	}
	return;
}

void Deck::ShuffleDeck(std::unordered_map<int, Card> oldDeckList)
{
	//for random positions
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(1,48);

	std::unordered_map<int, Card> shuffledDeck = oldDeckList;
	const int deckCount = 48;
	for(unsigned int i = deckCount - 1; i > 1; --i)
	{
		Card tempCard = shuffledDeck[i];
		unsigned int swapPos = distribution(generator);
		shuffledDeck[i] = shuffledDeck[swapPos];
		shuffledDeck[swapPos] = tempCard;
	}
	this->Cards = shuffledDeck;

	return;
}

void Deck::DealThreeHandDeck(std::unordered_map<int, Card> oldDeckList, std::vector<Player> & players)
{
	for(unsigned int i = 1; i < 48; i+=players.size())
		for(unsigned int j = 0; j < players.size(); j++)
		{
			// //sorted so we can just erase [0]
			if(i + j == kittySpots[0])
			{
				std::pair<int,Card> tempPair = std::make_pair(oldDeckList[i + j].GetRank(),oldDeckList[i + j]);
				//put card in kitty, go to next player and give them that card then continue as normal
				this->Kitty.push_back(tempPair);
				this->kittySpots.erase(this->kittySpots.begin());
				players[j].AddToHand(oldDeckList[(++i) + j]);
				continue;
			}
			players[j].AddToHand(oldDeckList[i + j]);
		}
	return;
}

void Deck::DealFourHandDeck(std::unordered_map<int, Card> oldDeckList, std::vector<Player> players)
{

}

void Deck::DealToKitty()
{
	//for random positions
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(1,47);

	//determine spots for kitty cards
	int kittyLocation = 0;
	while(kittySpots.size() != 3)
	{
		unsigned int kittyPos = distribution(generator);
		if(kittyLocation != 0)
		{
			// :3
			bool goodKitty = true;
			for(int i=0; i < this->kittySpots.size(); i++)
			{
				if((std::abs(this->kittySpots[i] - int(kittyPos)) != 1) &&
				    this->kittySpots[i] != kittyPos)
					continue;
				else
				{
				// >:3
					goodKitty = false;
					break;
				}
			}
			if(goodKitty) //:3 Ɛ:
			{
				this->kittySpots.push_back(kittyPos);
				kittyLocation++;
			}
			else
				continue;
		}
		else if(kittyLocation == 0)
		{
			this->kittySpots.push_back(kittyPos);
			kittyLocation++;
		}
		//bad spot picked, try again
		else
			continue;
	}
	//double check spots
	std::sort(this->kittySpots.begin(), this->kittySpots.end());
}

std::unordered_map<int, Card> Deck::CheckDeckList()
{
	return Cards;
	//going to have to rework this so it shows how many of each suit in each rank there still are
	//std::cout << GetCards() << GetSuits() << GetRanks() << std::endl;
}

int Deck::GetCards() { return cardCount; }

int Deck::GetSuits() { return suitCount; }

int Deck::GetRanks() { return rankCount; }

void Deck::SetCards(int newCardCount) { cardCount = newCardCount; }

void Deck::SetSuits(int newSuitCount) { suitCount = newSuitCount; }

void Deck::SetRanks(int newRankCount) { rankCount = newRankCount; }