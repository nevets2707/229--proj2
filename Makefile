


all : ssbros

Pos.o : Pos.cpp
	g++ -g -Wall -c Pos.cpp

simplehero.o : simplehero.cpp Pos.o
	g++ -g -Wall -c simplehero.cpp

ssbros : ssbros.cpp simplehero.o Pos.o
	g++ -g -Wall -o ssbros ssbros.cpp Actor.o GraphMap.o GameManager.o OtherActors.o simplehero.o Pos.o -lncurses

test : test.cpp
	g++ -g -Wall -o test test.cpp Pos.o -lncurses

clean:
	rm ssbros


tarball:
	tar czf project2.tar.gz Makefile *.hpp ssbros.cpp *.o maps/*.txt
