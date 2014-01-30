combo : main.cpp combination.o
	g++ -Wall -O3 -std=c++11 -o combo main.cpp combination.o -lboost_timer -lboost_system

combination.o : combination.h combination.cpp
	g++ -Wall -O3 -c -std=c++11 -o combination.o combination.cpp

