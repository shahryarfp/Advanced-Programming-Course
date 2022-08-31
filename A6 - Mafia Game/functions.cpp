#include "functions.hpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void split_command_line(string command, vector<string>& commands_in_line){
	string word;
	istringstream iss(command);
	while(getline(iss, word, ' '))
		commands_in_line.push_back(word);
}