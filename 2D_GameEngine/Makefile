CXX = g++
CXXFLAGS = -Wall -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image

# grab all .cpp files in this directory
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
EXEC = main

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)
