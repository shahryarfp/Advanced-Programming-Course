#include "functions.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define NUM_OF_SONG_DATAS 5
#define NUM_OF_LIKED_SONG_DATAS 4
using namespace std;

vector<Song> read_songs_file(char* argv[]){
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

vector<Liked_Song> read_liked_songs_file(char* argv[]){
	vector<Liked_Song> liked_songs;
	ifstream liked_song_file;
	liked_song_file.open(argv[2]);
	string line;
	string token;
	string delim = ",";
	getline(liked_song_file, line);
	while (getline(liked_song_file, line)){
		string username;
		string email;
		string password;
		int liked_song;
		auto start = 0U;
		auto end = line.find(delim);
		for (int i = 0; i < NUM_OF_LIKED_SONG_DATAS; i++){
			token = line.substr(start, end - start);
			if (i == 0)
				username = token;
			else if (i == 1)
				email = token;
			else if (i == 2)
				password = token;
			else if (i == 3)
				liked_song = stoi(token);

			start = end + delim.length();
			end = line.find(delim, start);
		}
		liked_songs.push_back(Liked_Song(username, email, password, liked_song));
	}
	liked_song_file.close();
	return liked_songs;
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
bool compare_al(Similarity v1, Similarity v2){
	return v1.username > v2.username;
}
vector<Similarity> sort_by_usern(vector<Similarity> SV){
	sort(SV.begin(), SV.end(), compare_al);
	return SV;
}

vector<Similarity> sort_by_similarity(vector<Similarity> SV){
	vector<Similarity> sv = SV;
	int j;
	Similarity key;
	int size = sv.size();
	for (int i = 1; i<size; i++){
		key = sv[i];
		j = i;
		while (true){
			if (j <= 0)
				break;
			if (key.similarity < sv[j-1].similarity)
				break;
			sv[j] = sv[j - 1];
			j--;
		}
		sv[j] = key;
	}
	return sv;
}
vector<Recom> sort_by_confidence(vector<Recom> CV){
	vector<Recom> cv = CV;
	int j;
	Recom key;
	int size = cv.size();
	for (int i = 1; i<size; i++){
		key = cv[i];
		j = i;
		while (true){
			if (j <= 0)
				break;
			if (key.confidence < cv[j-1].confidence)
				break;
			cv[j] = cv[j - 1];
			j--;
		}
		cv[j] = key;
	}
	return cv;
}