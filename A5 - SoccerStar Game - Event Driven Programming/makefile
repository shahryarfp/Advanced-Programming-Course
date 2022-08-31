CC = g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out

soccerStars.out: main.o table.o ball.o player.o functions.o rsdl.o
	${CC} main.o table.o ball.o player.o functions.o rsdl.o $(CCFLAGS) -o soccerStars.out


main.o: main.cpp table.hpp functions.hpp RSDL/src/rsdl.hpp
	${CC} -c main.cpp

table.o: table.hpp table.cpp player.hpp functions.hpp ball.hpp RSDL/src/rsdl.hpp
	${CC} -c table.cpp

rsdl.o: RSDL/src/rsdl.cpp RSDL/src/rsdl.hpp
	${CC} -c RSDL/src/rsdl.cpp

ball.o: ball.hpp ball.cpp RSDL/src/rsdl.hpp
	${CC} -c ball.cpp

player.o: player.hpp player.cpp RSDL/src/rsdl.hpp
	${CC} -c player.cpp

functions.o: functions.hpp functions.cpp RSDL/src/rsdl.hpp table.hpp
	${CC} -c functions.cpp

clean:
	rm *.o
	rm soccerStars.out