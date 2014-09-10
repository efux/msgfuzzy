#include <string>
#include <iostream>
#include <set>

#ifndef MSGIDENTRY_H
#define MSGIDENTRY_H value

class MsgIdEntry {
	private:
		int row;
		std::string file;
		std::string content;
		int levenshteinDistance(std::string, std::string);
		std::set<std::string> fuzzyEntries;

	public:
		MsgIdEntry(std::string line, int row, std::string file) ;
		std::string getContent();
		void addFuzzyEntry(std::string);
};

#endif
