#include <iostream>
#include <vector>
#include <string>
#include "game.hpp"

using namespace std;

int main() {
	string command;
	Game game;
	while (getline(cin,command)) {
		game.handle_command(command);
	}
	return 0;
}