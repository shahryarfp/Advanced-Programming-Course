CC = g++ -std=c++11

all: utunes.out

utunes.out: main.o functions.o utunes.o song.o user.o playlist.o\
 filter.o artistfilter.o yearfilter.o likefilter.o
	${CC} main.o functions.o utunes.o song.o user.o playlist.o \
		filter.o artistfilter.o yearfilter.o likefilter.o -o utunes.out


main.o: main.cpp utunes.hpp functions.hpp song.hpp
	${CC} -c main.cpp

utunes.o: utunes.cpp utunes.hpp functions.hpp song.hpp\
 exceptions.hpp user.hpp playlist.hpp filter.hpp\
  artistfilter.hpp yearfilter.hpp likefilter.hpp liked_songs.hpp
	${CC} -c utunes.cpp

functions.o: functions.cpp functions.hpp song.hpp liked_songs.hpp
	${CC} -c functions.cpp

song.o: song.cpp song.hpp exceptions.hpp
	${CC} -c song.cpp

user.o: user.cpp user.hpp exceptions.hpp functions.hpp song.hpp
	${CC} -c user.cpp

playlist.o: playlist.cpp playlist.hpp song.hpp exceptions.hpp functions.hpp
	${CC} -c playlist.cpp

filter.o: filter.cpp filter.hpp song.hpp
	${CC} -c filter.cpp

artistfilter.o: artistfilter.cpp artistfilter.hpp filter.hpp
	${CC} -c artistfilter.cpp

yearfilter.o: yearfilter.cpp yearfilter.hpp filter.hpp exceptions.hpp
	${CC} -c yearfilter.cpp

likefilter.o: likefilter.cpp likefilter.hpp filter.hpp exceptions.hpp
	${CC} -c likefilter.cpp

clean:
	rm *.o
	rm utunes.out