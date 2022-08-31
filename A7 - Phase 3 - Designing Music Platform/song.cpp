#include "song.hpp"
#include <iostream>
#include "exceptions.hpp"

vector<Comment> sort_by_username(vector<Comment> C){
	vector<Comment> comments = C;
	int j;
	Comment key;
	int size = comments.size();
	for (int i = 1; i<size; i++){
		key = comments[i];
		j = i;
		while (true){
			if (j <= 0)
				break;
			if (key.username > comments[j-1].username)
				break;
			comments[j] = comments[j - 1];
			j--;
		}
		comments[j] = key;
	}
	return comments;
}

vector<Comment> sort_by_time(vector<Comment> C){
	vector<Comment> comments = C;
	int j;
	Comment key;
	int size = comments.size();
	for (int i = 1; i<size; i++){
		key = comments[i];
		j = i;
		while (true){
			if (j <= 0)
				break;
			if (key.time > comments[j-1].time)
				break;
			comments[j] = comments[j - 1];
			j--;
		}
		comments[j] = key;
	}
	return comments;
}

Song::Song(int id_, string title_, string artist_, 
		int release_year_, string link_){
	id = id_;
	title = title_;
	artist = artist_;
	release_year = release_year_;
	link = link_;
	num_of_likes = 0;
	num_of_comments = 0;
	num_of_playlists = 0;
}
void Song::print_info(){
	cout << id << endl;
	cout << title << endl;
	cout << artist << endl;
	cout << release_year << endl;
	cout << "#likes: " << num_of_likes << endl;
	cout << "#comments: " << num_of_comments << endl;
	cout << "#playlists: " << num_of_playlists << endl;
}
void Song::add_comment(Comment comment){
	comments.push_back(comment);
	num_of_comments++;
}

void Song::print_comments(vector<string> commands_in_line){
	if(comments.size() == 0)
		throw Empty();
	comments = sort_by_username(comments);
	comments = sort_by_time(comments);
	for(int i=0; i<comments.size(); i++){
		cout << comments[i].time << " ";
		cout << comments[i].username << ": ";
		cout << comments[i].comment << endl;
	}
}