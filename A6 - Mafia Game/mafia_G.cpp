#include "mafia_G.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Mafia_G::Mafia_G(string name)
	:Player(name)
{

}

void Mafia_G::day_died(){
	status = "mafia died";
	alive = false;
	cout << name << " died\n";
}

bool Mafia_G::is_mafia(){
	return true;
}

void Mafia_G::handle_kill(){
	alive = false;
	cout << name << " was killed" << endl;
	status = "mafia died";
}