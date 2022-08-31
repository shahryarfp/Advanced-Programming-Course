#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <iostream>
#include <vector>
#include "song.hpp"
#include "exceptions.hpp"
#include "functions.hpp"
using namespace std;

class Playlist{
public:
	Playlist(string name_, bool is_private_, int id_, string username_);
	string get_username(){return username;}
	void print_all(bool& is_empty);
	void print_publics(bool& is_empty);
	int get_id(){return id;}
	void add_song(Song* song);
	bool get_is_private(){return is_private;}
	void print_songs(bool& is_empty);
	void delete_song(int song_id);
private:
	string name;
	vector<Song*> songs;
	bool is_private;
	int id;
	string username;
};



#endif