#ifndef PUTIL_H
#define PUTIL_H

#include "card.h"

#include <vector>

namespace PUtil
{
	std::vector<int> GetVectorofRanks(std::vector<Card> inCards);
}

#endif