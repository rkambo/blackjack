target clean:
	rm *.out

target all:
	clang++ -std=c++11 src/cards.cpp -o bin/runMe.out
	./bin/runMe.out