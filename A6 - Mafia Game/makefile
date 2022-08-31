CC = g++ -std=c++11

all: mafia.out

mafia.out: main.o player.o functions.o game.o joker.o mafia_G.o mafia.o\
 villager_G.o villager.o silencer.o godfather.o detective.o doctor.o bulletproof.o
	${CC} main.o player.o functions.o game.o joker.o mafia_G.o mafia.o villager_G.o\
	 villager.o silencer.o godfather.o detective.o doctor.o bulletproof.o -o mafia.out

main.o: main.cpp game.hpp
	${CC} -c main.cpp

functions.o: functions.cpp functions.hpp player.hpp
	${CC} -c functions.cpp

game.o: game.cpp game.hpp functions.hpp exceptions.hpp player.hpp joker.hpp
	${CC} -c game.cpp

player.o: player.cpp player.hpp
	${CC} -c player.cpp


joker.o: joker.cpp joker.hpp player.hpp
	${CC} -c joker.cpp



mafia_G.o: mafia_G.cpp mafia_G.hpp player.hpp
	${CC} -c mafia_G.cpp

mafia.o: mafia.cpp mafia.hpp mafia_G.hpp player.hpp
	${CC} -c mafia.cpp

godfather.o: godfather.cpp godfather.hpp mafia_G.hpp player.hpp
	${CC} -c godfather.cpp

silencer.o: silencer.cpp silencer.hpp mafia_G.hpp player.hpp exceptions.hpp
	${CC} -c silencer.cpp




villager_G.o: villager_G.cpp villager_G.hpp player.hpp
	${CC} -c villager_G.cpp

villager.o: villager.cpp villager.hpp villager_G.hpp player.hpp
	${CC} -c villager.cpp

detective.o: detective.cpp detective.hpp villager_G.hpp player.hpp exceptions.hpp
	${CC} -c detective.cpp

doctor.o: doctor.cpp doctor.hpp villager_G.hpp player.hpp exceptions.hpp
	${CC} -c doctor.cpp

bulletproof.o: bulletproof.cpp bulletproof.hpp villager_G.hpp player.hpp exceptions.hpp
	${CC} -c bulletproof.cpp

clean:
	rm *.o
	rm mafia.out