#include <string>
#include <iostream>

#ifndef MSGIDENTRY_H
#define MSGIDENTRY_H value

class MsgIdEntry {
	private:

	public:
		MsgIdEntry(std::string line, int row, std::string file) {
			std::cout << line << row << std::endl ;	
		}
};

#endif
