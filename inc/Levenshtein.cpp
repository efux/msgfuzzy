#include <map>
#include <string>
#include <iostream>
#include "Levenshtein.h"

Levenshtein::Levenshtein(std::string first, std::string second)
{
	this->first = first;
	this->second = second;
}

int Levenshtein::calculate()
{
	return calculate(first, second);
}

int Levenshtein::calculate(std::string first, std::string second)
{
	int cost = 0;

	if(DM.find(GridPosition(first.length(), second.length())) != DM.end()) {
		return DM.at(GridPosition(first.length(), second.length()));
	}

	if(first == second || first == "" || second == "") {
		return cost;
	}

	if(first.at(0) == second.at(0)) {
		return calculate(first.substr(1), second.substr(1));
	}

	int costReplacement = calculate(first.substr(1), second.substr(1));
	int costInsertion = calculate(first, second.substr(1));
	int costDeletion = calculate(first.substr(1), second);

	if(costReplacement <= costInsertion && costReplacement <= costDeletion) {
		cost = costReplacement;
		cost += WEIGHT_REPLACEMENT;
	} else {
		if(costInsertion <= costReplacement && costInsertion <= costDeletion) {
			cost = costInsertion;
		} else {
			cost = costDeletion;
		}
		cost += WEIGHT_INSDEL;
	}


	DM.insert(std::make_pair(GridPosition(first.length(), second.length()),cost));
	return cost;
}
