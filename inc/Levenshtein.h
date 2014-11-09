#include <map>
#include <string>
#include "GridPosition.h"

#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#define WEIGHT_REPLACEMENT 1
#define WEIGHT_INSDEL 1

class Levenshtein {
	private:
		std::map<GridPosition, int> DM;
		std::string first,second;
		int calculate(std::string first, std::string second);
	public:
		Levenshtein (std::string first, std::string second);
		int calculate();
	
};

#endif
