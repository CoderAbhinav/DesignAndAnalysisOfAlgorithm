build: main.cpp
	g++ main.cpp -o main

run: main
	./main < input.txt > output.txt
	cat output.txt

clean: output.txt main
	rm main
	rm output.txt