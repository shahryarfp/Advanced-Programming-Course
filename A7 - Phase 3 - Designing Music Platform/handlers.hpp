#ifndef HANDLERS
#define HANDLERS

#include "server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "utunes.hpp"

class show_first_page : public RequestHandler {
public:
  Response *callback(Request *);
};

class handle_logout : public RequestHandler {
public:
	handle_logout(Utunes* utunes_){
		utunes = utunes_;
	}
	Response *callback(Request *);
private:
	Utunes* utunes;
};

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Utunes* utunes_){
		utunes = utunes_;
	}
	Response *callback(Request *);
private:
	Utunes* utunes;
};

class signupHandler : public RequestHandler {
public:
	signupHandler(Utunes* utunes_){
		utunes = utunes_;
	}
	Response *callback(Request *);
private:
	Utunes* utunes;
};

class handle_user_homepage : public RequestHandler {
public:
	handle_user_homepage(Utunes* utunes_){
		utunes = utunes_;
	}
	Response *callback(Request *);
private:
	Utunes* utunes;
};

class handle_errors : public RequestHandler {
public:
  Response *callback(Request *);
};

#endif

class handle_song_info : public RequestHandler {
public:
	handle_song_info(Utunes* utunes_){
		utunes = utunes_;
	}
	Response *callback(Request *);
private:
	Utunes* utunes;
};