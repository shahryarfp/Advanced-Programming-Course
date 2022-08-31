#include <iostream>
#include "song.hpp"
#include "functions.hpp"
#include "utunes.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	vector<Song> songs = ReadFile(argv);
	Utunes utunes = Utunes(songs);
	string command;
	while (getline(cin,command)) {
		utunes.handle_command(command);
	}
	return 0;
}