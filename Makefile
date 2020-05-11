Lab8: Instantiation.o
	g++ -o Lab8 Instantiation.o

Instantiation.o: Instantiation.cpp
	g++ -c -Wall -std=c++11 Instantiation.cpp -g
clean:
	rm -f Test Instantiation.o
rebuild:
	make clean
	make
