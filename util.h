#ifndef PUTIL_H
#define PUTIL_H

#include <vector>
#include <string>
#include "card.h"

namespace PUtil
{
	std::vector<int> GetVectorofRanks(std::vector<Card> inCards);
}

#endif