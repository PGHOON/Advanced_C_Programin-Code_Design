CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lncurses
SRC_DIR = src
EXECUTABLE = game

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXECUTABLE) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean