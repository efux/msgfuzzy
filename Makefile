SRCS = $(shell find -name '*.cpp')
LIBS=
EXECUTABLE=msgfuzzy

all:
	@echo "** Building msgfuzzy"
	g++ -lboost_regex -Iinc/ $(SRCS) -o $(EXECUTABLE) $(LIBS) -std=c++11 -g -Wall

clean:
	@echo "** Removing object files and executable..."
	rm -f *.o
