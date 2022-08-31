#ifndef UTUNES_HPP
#define UTUNES_HPP

#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "song.hpp"
#include "liked_songs.hpp"
#include "exceptions.hpp"
#include "user.hpp"
#include "playlist.hpp"
#include "functions.hpp"
#include "filter.hpp"
#include "artistfilter.hpp"
#include "yearfilter.hpp"
#include "likefilter.hpp"
#include "server/server.hpp"

using namespace std;

class Utunes{
public:
	Utunes(vector<Song> songs_, vector<Liked_Song> liked_songs_);
	ostringstream make_songs_body();
	ostringstream make_song_info_body(int id_);
	void handle_command(string command);
	void handle_signup(vector<string> commands_in_line);
	void handle_login(vector<string> commands_in_line);
	void handle_logout();
	void userssize(){cout<<users.size();}
private:
	void handle_get_songs_list(vector<string> commands_in_line);
	void handle_get_song(vector<string> commands_in_line);
	void handle_like_song(vector<string> commands_in_line);
	void handle_get_likes(vector<string> commands_in_line);
	void handle_delete_likes(vector<string> commands_in_line);
	void handle_post_playlists(vector<string> commands_in_line);
	void handle_get_playlists(vector<string> commands_in_line);
	void handle_post_playlists_songs(vector<string> commands_in_line);
	void handle_get_playlists_songs(vector<string> commands_in_line);
	void handle_delete_playlists_songs(vector<string> commands_in_line);
	void handle_get_users(vector<string> commands_in_line);
	void handle_filters(vector<string> commands_in_line);
	void handle_delete_filters(vector<string> commands_in_line);
	void handle_post_comments(vector<string> commands_in_line);
	void handle_get_comments(vector<string> commands_in_line);
	void handle_throws(vector<string> commands_in_line);
	void add_liked_songs(vector<Liked_Song> liked_songs_);
	void update_users_and_songs_matrix();
	void update_similarity_matrix();
	void handle_similar_users(vector<string> commands_in_line);
	void handle_recommended(ostringstream &body);
	double calculate_confidence(int song);

	vector<User> users;
	vector<Song> songs;
	vector<Song> filtered_songs;
	int enterd_user;
	vector<Playlist> playlists;
	map<string,string> filters;
	vector<vector<int>> users_and_songs_matrix;
	vector<vector<double>> similarity_matrix;
};

#endif