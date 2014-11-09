#include <vector>
#include <boost/regex.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "FuzzyParser.h"
#include "MsgIdEntry.h"

FuzzyParser::FuzzyParser() : files(), entries()
{
}

void FuzzyParser::addFile(std::string filename)
{
	std::ifstream file(filename);
	if(file) {
		files.push_back(filename);
	} else {
		std::cout << "File " << filename << " not found!\n";
	}
}

void FuzzyParser::startSearch()
{
	// load every po-file
	if(files.size()>0) {
		loadFiles();	
		compareMsgIds();
		printFuzzyEntries();
	} else {
		std::cout << "msgfuzzy: no input files given" << std::endl
			<< "Try `msgfuzzy --help` for more information." << std::endl;
	}
}

void FuzzyParser::loadFiles()
{
	bool trigger = false;
	std::string line;
	// open all the valid files submitted via arguments
	for(auto file : files) {
		std::ifstream poFile(file);
		if(poFile.is_open()) {
			int row = 1 ;
			// read all lines of this file
			while(getline(poFile, line)) {

				// if this line of the file contains msgid "..." add it to the vector
				if(isMsgIdLine(line)) {

					entries.push_back(MsgIdEntry(line, row, file));
					trigger = true;
				}

				if(isMsgStrLine(line) && trigger) {
					entries[entries.size()-1].addMsgStr(line);
					trigger = false;
				}

				row++;
			}
			poFile.close();
		}
	}
}

bool FuzzyParser::isMsgIdLine(std::string line)
{
	static const boost::regex reg("^msgid \"(.+)\"", boost::regex::icase);
	return boost::regex_match(line, reg);
}

bool FuzzyParser::isMsgStrLine(std::string line)
{
	static const boost::regex reg("^msgstr \"(.+)\"", boost::regex::icase);
	return boost::regex_match(line, reg);
}

void FuzzyParser::compareMsgIds()
{
	// O(n^2)
	for(auto& second : entries) {
		for(auto& first : entries) {
			if(first.getContent() != second.getContent()) {
				if(!second.containsEntry(first.getContent())) {
					if(second.compareTo(first.getContent())) {
						first.addFuzzyEntry(second.getContent());
						second.addFuzzyEntry(first.getContent());
					}
				}		
			}
		}
	}
}

void FuzzyParser::printFuzzyEntries()
{
	for(auto entry : entries) {
		entry.printEntry();
		std::cout << std::endl;
	}
}
