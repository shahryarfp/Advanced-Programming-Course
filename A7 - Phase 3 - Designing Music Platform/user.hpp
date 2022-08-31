#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include "song.hpp"
#include "exceptions.hpp"
#include "functions.hpp"

using namespace std;

class User{
public:
	User(string email_, string username_, string password_);
	string get_email(){return email;}
	string get_username(){return username;}
	string get_password(){return password;}
	vector<Song*> get_liked_songs(){return liked_songs;}
	bool is_liked(Song* song);
	void add_to_likes(Song* song);
	void add_initial_likes(Song* song);
	void delete_from_likes(Song* song);
	void print_likes();
private:
	string email;
	string username;
	string password;
	vector<Song*> liked_songs;
};



#endif