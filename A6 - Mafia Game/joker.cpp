#include "joker.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Joker::Joker(string name)
	: Player(name)
{

}
void Joker::day_died(){
	alive = false;
	cout << name << " died\n";
	status = "Joker won";
}
bool Joker::is_mafia(){
	return false;
}
void Joker::handle_kill(){
	alive = false;
	cout << name << " was killed" << endl;
}