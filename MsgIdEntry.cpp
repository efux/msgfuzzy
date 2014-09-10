#include <string>
#include <vector>
#include <boost/regex.hpp>
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
