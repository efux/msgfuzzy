#include <vector>
#include <string>
#include "MsgIdEntry.h"

#ifndef FUZZYPARSER_H
#define FUZZYPARSER_H

class FuzzyParser {
	private:
		std::vector<std::string> files;	
		std::vector<MsgIdEntry> entries;
		void loadFiles();
		bool isMsgIdLine(std::string line);

	public:
		FuzzyParser () ;
		void addFile(std::string filename) ;
		void startSearch();
};

#endif
