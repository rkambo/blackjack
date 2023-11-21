target clean:
	rm *.out

target all:
	clang++ -std=c++11 -I include/* src/main.cpp -o bin/runMe.out
	./bin/runMe.out