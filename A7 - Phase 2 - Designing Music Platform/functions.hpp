#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include "song.hpp"
#include "liked_songs.hpp"

using namespace std;
typedef struct Similarity{
	string username;
	double similarity;
}Similarity;
typedef struct Recom{
	int song_id;
	double confidence;
}Recom;
vector<string> split_command_line(string command);
vector<Song> read_songs_file(char* argv[]);
vector<Liked_Song> read_liked_songs_file(char* argv[]);
bool compare_id_pointer(Song* s1, Song* s2);
vector<Song*> sort_by_id_pointer(vector<Song*> song_list);
bool compare_id(Song s1, Song s2);
vector<Song> sort_by_id(vector<Song> song_list);
bool compare_alphabetically(string v1, string v2);
vector<string> sort_alphabetically(vector<string> V);
vector<Similarity> sort_by_usern(vector<Similarity> SV);
vector<Similarity> sort_by_similarity(vector<Similarity> SV);
vector<Recom> sort_by_confidence(vector<Recom> CV);

#endif