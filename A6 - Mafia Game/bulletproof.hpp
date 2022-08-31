#ifndef BULLETPROOF_HPP
#define BULLETPROOF_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "villager_G.hpp"

using namespace std;

class Bulletproof : public Villager_G{
public:
	Bulletproof(string name);
	virtual void handle_kill();
private:
	bool protect;
};

#endif