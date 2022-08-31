#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "player.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct Enrolled_Player{
	string name;
	string role;
}Enrolled_Player;

typedef struct Votes_help{
	string name;
	int num_of_votes;
}Votes_help;

void split_command_line(string command, vector<string>& commands_in_line);

#endif