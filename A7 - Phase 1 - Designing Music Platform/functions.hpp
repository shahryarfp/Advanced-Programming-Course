#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <algorithm>
#include <iostream>
#include "song.hpp"


using namespace std;

vector<string> split_command_line(string command);
vector<Song> ReadFile(char* argv[]);
bool compare_id_pointer(Song* s1, Song* s2);
vector<Song*> sort_by_id_pointer(vector<Song*> song_list);
bool compare_id(Song s1, Song s2);
vector<Song> sort_by_id(vector<Song> song_list);
bool compare_alphabetically(string v1, string v2);
vector<string> sort_alphabetically(vector<string> V);
#endif