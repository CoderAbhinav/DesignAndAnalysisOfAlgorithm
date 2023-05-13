CXX = g++
CXXFLAGS = -std=c++17

.PHONY: all clean

all: compile run

compile:
	$(CXX) $(CXXFLAGS) -o main.bin main.cpp

run: main.bin input.txt
	./main.bin < input.txt > output.txt

clean:
	rm -f main.bin output.txt
