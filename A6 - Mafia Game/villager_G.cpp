#include "villager_G.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Villager_G::Villager_G(string name)
	:Player(name)
{

}
void Villager_G::day_died(){
	status = "villager died";
	alive = false;
	cout << name << " died\n";
}
bool Villager_G::is_mafia(){return false;}
void Villager_G::handle_kill(){
	alive = false;
	cout << name << " was killed" << endl;
	status = "villager died";
}