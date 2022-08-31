CC = g++ -std=c++11

all: utunes.out

utunes.out: main.o functions.o utunes.o song.o user.o playlist.o\
 filter.o artistfilter.o yearfilter.o likefilter.o my_server.o\
  handlers.o response.o request.o utilities.o\
   server.o route.o template_parser.o
	
	${CC} main.o functions.o utunes.o song.o user.o playlist.o \
		filter.o artistfilter.o yearfilter.o likefilter.o my_server.o\
		handlers.o response.o request.o utilities.o\
		server.o route.o template_parser.o -o utunes.out


main.o: main.cpp utunes.hpp functions.hpp song.hpp server/server.hpp \
utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} -c main.cpp

utunes.o: utunes.cpp utunes.hpp functions.hpp song.hpp\
 exceptions.hpp user.hpp playlist.hpp filter.hpp\
  artistfilter.hpp yearfilter.hpp likefilter.hpp liked_songs.hpp\
  server/server.hpp
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




template_parser.o: utils/template_parser.cpp utils/template_parser.hpp\
 utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp\
 utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp\
  utils/template_parser.cpp
	$(CC) -c server/server.cpp

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp\
 utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp

handlers.o: handlers.cpp handlers.hpp server/server.hpp utils/utilities.hpp\
 utils/response.hpp utils/request.hpp utils/include.hpp utunes.hpp
	$(CC) -c handlers.cpp

my_server.o: my_server.cpp my_server.hpp server/server.hpp utils/utilities.hpp\
 utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c my_server.cpp

clean:
	rm *.o
	rm utunes.out