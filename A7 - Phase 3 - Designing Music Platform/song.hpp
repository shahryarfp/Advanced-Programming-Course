#ifndef SONG_HPP
#define SONG_HPP

#include <iostream>
#include <vector>

using namespace std;

typedef struct Comment{
	int time;
	string username;
	string comment;
}Comment;

class Song{
public:
	Song(int id_, string title_, string artist_, 
		int release_year_, string link_);
	int get_id(){return id;}
	string get_title(){return title;}
	string get_artist(){return artist;}
	string get_link(){return link;}
	int get_released_year(){return release_year;}
	void print_info();
	int get_num_of_likes(){return num_of_likes;}
	int get_num_of_playlists(){return num_of_playlists;}
	void add_comment(Comment comment);
	void print_comments(vector<string> commands_in_line);
	void increase_likes(){num_of_likes++;}
	void decrease_likes(){num_of_likes--;}
	void increase_playlists(){num_of_playlists++;}
	void decrease_playlists(){num_of_playlists--;}
private:
	int id;
	string title;
	string artist;
	int release_year;
	string link;
	int num_of_likes;
	int num_of_comments;
	int num_of_playlists;
	vector<Comment> comments;
};



#endif