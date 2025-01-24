CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

TARGET = simple_mahjong
SOURCES = main.cpp Tile.hpp Stack.hpp Mahjong_Hand.hpp Parser.hpp
OBJECTS = main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)
