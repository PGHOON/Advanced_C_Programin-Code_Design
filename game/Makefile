CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lncurses

SRC = main.cpp ui.cpp

all: game

game: $(SRC)
	$(CXX) $(CXXFLAGS) -o game $(SRC) $(LIBS)

clean:
	rm -f game

.PHONY: all clean
