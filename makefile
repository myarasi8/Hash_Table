SHELL:=/bin/bash

all:
	module load gcc
	g++ -std=c++0x -o a main.cpp CuckooHashTable.cpp
clean:
	rm a