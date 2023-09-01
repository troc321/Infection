CXX = g++
CXXFLAGS = -g -Wall -O0

infectsim: Board.o main.o Human.o MaskedHuman.o conio.o
	g++ -g -Wall -O0 Board.o main.o Human.o MaskedHuman.o conio.o
Board.o: Board.cpp Board.h conio.cpp conio.h 

Human.o: Board.cpp Board.h Human.cpp Human.h conio.cpp conio.h

MaskedHuman.o: Board.cpp Board.h Human.cpp Human.h MaskedHuman.cpp MaskedHuman.h conio.cpp conio.h

main.o: Board.cpp Board.h main.cpp 

conio.o: conio.cpp conio.h

clean: 
	rm -f *.o infection
