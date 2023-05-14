CXX = g++
CXXFLAGS = -std=c++17

.PHONY: all clean

all: compile run

compile:
	$(CXX) $(CXXFLAGS) -o main.bin main.cpp

run: main.bin
	./main.bin > output.txt

clean:
	rm -f main.bin output.txt
