#include <iostream>
#include <cstring>
#include "FuzzyParser.h"

void print_usage();
void parse_argument(const char* arg);

FuzzyParser fuzzyParser;

int main(int argc, const char* argv[])
{
	// parsing arguments
	for(int i=1; i < argc; i++) {
		parse_argument(argv[i]) ;
	}
	fuzzyParser.startSearch();

	return 0;
}

void print_usage()
{
	std::cout << "Usage: msgfuzzy [OPTION] def.po\n\n"
		<< "This programm finds fuzzy entries in the msgids of the passed def.po file\n"
		<< "The output has to be verified by the user because the fuzzy entries aren't\n"
		<< "necessarily unwanted.\n\n"
		<< "Parameters:\n"
		<< "\t-h\t\t\tPrint this usage help\n" ;
}

void parse_argument(const char* arg)
{
	if(strcmp(arg,"-h")==0) {
		print_usage();
		return;
	}

	// the submitted argument has to be a file
	fuzzyParser.addFile(arg) ;
}
