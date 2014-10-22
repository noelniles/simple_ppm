all: main.o ppm.o
	g++ -Wall -Wextra -Wpedantic main.o ppm.o -o ppm

main.o: main.cc ppm.h
	g++ -Wall -Wextra -Wpedantic -c main.cc ppm.h

ppm.o: ppm.cc
	g++ -Wall -Wextra -Wpedantic -c ppm.cc

