
wordrange: main.o wordrange.o
	g++ main.o wordrange.o -o wordrange
main.o: main.cpp
	g++ -c main.cpp
wordrange.o: wordrange.cpp wordrange.h
	g++ -c wordrange.cpp
clean:
	rm *.o wordrange
