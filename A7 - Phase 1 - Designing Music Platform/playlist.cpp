#include "playlist.hpp"
#include <iostream>

Playlist::Playlist(string name_, bool is_private_, int id_, string username_){
	name = name_;
	is_private = is_private_;
	id = id_;
	username = username_;
}
void Playlist::print_all(bool& is_empty){
	is_empty = false;
	cout << id << " ";
	cout << name << " ";
	if(is_private)
		cout << "private" << endl;
	else
		cout << "public" << endl;
}
void Playlist::print_publics(bool& is_empty){
	if(!is_private){
		is_empty = false;
		cout << id << " ";
		cout << name << " ";
		cout << "public" << endl;
	}
}

void Playlist::add_song(Song* song){
	songs.push_back(song);
	song->increase_playlists();
}
void Playlist::print_songs(bool& is_empty){
	if(songs.size() == 0)
		throw Empty();
	songs = sort_by_id_pointer(songs);
	for(int i=0; i<songs.size(); i++){
		cout << songs[i]->get_id() << " ";
		cout << songs[i]->get_title() << " ";
		cout << songs[i]->get_artist() << " ";
		cout << songs[i]->get_released_year() << endl;
	}
}

void Playlist::delete_song(int song_id){
	bool song_found = false;
	for(int i=0; i<songs.size(); i++){
		if(songs[i]->get_id() == song_id){
			song_found = true;
			songs.erase(songs.begin() + i);
			cout << "OK" << endl;
		}
	}
	if(!song_found)
		throw Bad_Request();
}