#include <iostream>
#include "song.hpp"
#include "functions.hpp"
#include "utunes.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	vector<Song> songs = read_songs_file(argv);
	vector<Liked_Song> liked_songs = read_liked_songs_file(argv);
	Utunes utunes = Utunes(songs, liked_songs);
	string command;
	while (getline(cin,command)) {
		utunes.handle_command(command);
	}
	return 0;
}