#include "functions.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define NUM_OF_SONG_DATAS 5

using namespace std;

vector<Song> ReadFile(char* argv[]){
	vector<Song> songs;
	ifstream song_file;
	song_file.open(argv[1]);
	string line;
	string token;
	string delim = ",";
	getline(song_file, line);
	while (getline(song_file, line)){
		int id;
		string title;
		string artist;
		int release_year;
		string link;
		auto start = 0U;
		auto end = line.find(delim);
		for (int i = 0; i < NUM_OF_SONG_DATAS; i++){
			token = line.substr(start, end - start);
			if (i == 0)
				id = stoi(token);
			else if (i == 1)
				title = token;
			else if (i == 2)
				artist = token;
			else if (i == 3)
				release_year = stoi(token);
			else if (i == 4)
				link = token;
			start = end + delim.length();
			end = line.find(delim, start);
		}
		songs.push_back(Song(id, title, artist, release_year, link));
	}
	song_file.close();
	return songs;
}

vector<string> split_command_line(string command){
	vector<string> commands_in_line;
	string word;
	istringstream iss(command);
	while(getline(iss, word, ' '))
		commands_in_line.push_back(word);
	return commands_in_line;
}
bool compare_id_pointer(Song* s1, Song* s2){
	return s1->get_id() < s2->get_id();
}
vector<Song*> sort_by_id_pointer(vector<Song*> song_list){
	sort(song_list.begin(), song_list.end(), compare_id_pointer);
	return song_list;
}
bool compare_id(Song s1, Song s2){
	return s1.get_id() < s2.get_id();
}
vector<Song> sort_by_id(vector<Song> song_list){
	sort(song_list.begin(), song_list.end(), compare_id);
	return song_list;
}
bool compare_alphabetically(string v1, string v2){
	return v1 < v2;
}
vector<string> sort_alphabetically(vector<string> V){
	sort(V.begin(), V.end(), compare_alphabetically);
	return V;
}
