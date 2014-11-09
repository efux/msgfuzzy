#include <string>
#include <iostream>
#include <set>

#ifndef MSGIDENTRY_H
#define MSGIDENTRY_H value

#define MAX_EDIT_DISTANCE 15
#define ENABLE_SMART_MATCH 1
#define MAX_EDIT_PERCENTAGE 0.2

class MsgIdEntry {
	private:
		int row;
		std::string file;
		std::string content;
		std::string msgstr = "msgstr \"\"";
		int levenshteinDistance(std::string, std::string);
		std::set<std::string> fuzzyEntries;

	public:
		MsgIdEntry(std::string line, int row, std::string file) ;
		std::string getContent();
		void addFuzzyEntry(std::string);
		void addMsgStr(std::string);
		bool containsEntry(std::string);
		bool compareTo(std::string);
		void printEntry();
};

#endif
