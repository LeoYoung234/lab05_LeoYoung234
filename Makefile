CXX = g++
CXXFLAGS = -g --std=c++20 -Wall

BINARIES = game game_set

all: ${BINARIES}

game_set: card.o main_set.o
	${CXX} ${CXXFLAGS} $^ -o game_set

game: card.o card_list.o main.o
	${CXX} ${CXXFLAGS} $^ -o game

tests: card.o card_list.o tests.o
	${CXX} ${CXXFLAGS} $^ -o tests
	./tests

main_set.o: main_set.cpp
	${CXX} ${CXXFLAGS} $^ -c

main.o: main.cpp
	${CXX} ${CXXFLAGS} $^ -c

tests.o: tests.cpp
	${CXX} ${CXXFLAGS} $^ -c

card_list.o: card_list.cpp card_list.h
	${CXX} ${CXXFLAGS} card_list.cpp -c

card.o: card.cpp card.h
	${CXX} ${CXXFLAGS} card.cpp -c

clean:
	rm -rf *.o ${BINARIES}
