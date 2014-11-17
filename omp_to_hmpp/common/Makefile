CC=g++
CFLAGS=-I
SOURCES=test.cpp PerformanceLap.cpp PerformanceLap.h
EXECUTABLE=test
.PHONY : clean install
all: 
	$(CC) inline.cpp -o inline
	$(CC) outline.cpp -o outline
inline:
	$(CC) inline.cpp -o inline
outline:
	$(CC) outline.cpp -o outline
clean:
	rm *.out *.o 

	

	

