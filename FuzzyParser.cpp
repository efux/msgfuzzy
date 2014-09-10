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
	} else {
		std::cout << "msgfuzzy: no input files given" << std::endl
		   << "Try `msgfuzzy --help` for more information." << std::endl;
	}
}

void FuzzyParser::loadFiles()
{
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
