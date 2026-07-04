CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

TARGET   := minesweeper_game

SRCS     := main.cpp sweeper_array_gen.cpp
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp sweeper_array_gen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean