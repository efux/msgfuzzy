#include <string>
#include <vector>
#include <boost/regex.hpp>
#include "Levenshtein.h"
#include "MsgIdEntry.h"

MsgIdEntry::MsgIdEntry(std::string line, int row, std::string file)
{
	this->row = row;
	this->file = file;

	unsigned int first = line.find("\"");
	unsigned int last = line.find_last_of("\"");
	content = line.substr(first+1, last-first-1);
}

std::string MsgIdEntry::getContent()
{
	return content;
}

void MsgIdEntry::addFuzzyEntry(std::string entry)
{
	fuzzyEntries.insert(entry);
}

bool MsgIdEntry::compareTo(std::string other)
{
	Levenshtein ls(content, other);
	if(ENABLE_SMART_MATCH!=1) {
		if(ls.calculate() < MAX_EDIT_DISTANCE) {
			return true;
		}
	} else {
		if(ls.calculate() < ((content.length() + other.length())/2)*MAX_EDIT_PERCENTAGE) {
			return true;
		}
	}
	return false;
}

bool MsgIdEntry::containsEntry(std::string entry) {
	if(fuzzyEntries.find(entry)!=fuzzyEntries.end()) {
		return true;
	}
	return false;
}

void MsgIdEntry::printEntry()
{
	if(fuzzyEntries.size() > 0) {
		std::cout << "# MsgFuzzy on line " << row << std::endl;
		for(auto entry : fuzzyEntries) {
			std::cout << "# " << entry << std::endl;
		}
	}
	std::cout << "msgid \"" << content << "\"" << std::endl;
	std::cout << msgstr << std::endl;
}

void MsgIdEntry::addMsgStr(std::string msgstr)
{
	this->msgstr = msgstr;
}
