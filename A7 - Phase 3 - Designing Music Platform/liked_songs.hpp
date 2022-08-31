#ifndef LIKED_SONG_HPP
#define LIKED_SONG_HPP

#include <iostream>
#include <vector>

using namespace std;

class Liked_Song{
public:
	Liked_Song(string username_, string email_, string password_, int liked_song_){
		username = username_;
		email = email_;
		password = password_;
		liked_song = liked_song_;
	}
	string get_username(){return username;}
	string get_email(){return email;}
	string get_password(){return password;}
	int get_liked_song(){return liked_song;}
private:
	string username;
	string email;
	string password;
	int liked_song;
};



#endif