#include "user.hpp"
#include <iostream>

User::User(string email_, string username_, string password_){
	email = email_;
	username = username_;
	password = password_;
}
void User::add_to_likes(Song* song){
	for(int i=0; i<liked_songs.size(); i++){
		if(liked_songs[i]->get_id() == song->get_id()){
			throw Bad_Request();
		}
	}
	song->increase_likes();
	liked_songs.push_back(song);
	cout << "OK" << endl;
}
void User::add_initial_likes(Song* song){
	for(int i=0; i<liked_songs.size(); i++){
		if(liked_songs[i]->get_id() == song->get_id()){
			throw Bad_Request();
		}
	}
	song->increase_likes();
	liked_songs.push_back(song);
}
void User::print_likes(){
	if(liked_songs.size() == 0)
		throw Empty();
	liked_songs = sort_by_id_pointer(liked_songs);
	for(int i=0; i<liked_songs.size(); i++){
		cout << liked_songs[i]->get_id() << " ";
		cout << liked_songs[i]->get_title() << " ";
		cout << liked_songs[i]->get_artist() << " ";
		cout << liked_songs[i]->get_released_year() << endl;
	}
}

void User::delete_from_likes(Song* song){
	for(int i=0; i<liked_songs.size(); i++){
		if(liked_songs[i]->get_id() == song->get_id()){
			liked_songs.erase(liked_songs.begin() + i);
			song->decrease_likes();
			cout << "OK" << endl;
			return;
		}
	}
	throw Bad_Request();
}

bool User::is_liked(Song* song){
	for(int i=0; i<liked_songs.size(); i++){
		if(liked_songs[i]->get_id() == song->get_id()){
			return true;
		}
	}
	return false;
}