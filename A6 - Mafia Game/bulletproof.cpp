#include "bulletproof.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Bulletproof::Bulletproof(string name)
	:Villager_G(name)
{
	protect = true;
}

void Bulletproof::handle_kill(){
	if(!protect){
		alive = false;
		cout << name << " was killed" << endl;
		status = "villager died";
	}
	else{
		protect = false;
	}
}