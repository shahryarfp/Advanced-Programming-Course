#ifndef VILLAGER_G_HPP
#define VILLAGER_G_HPP

#include <iostream>
#include <vector>
#include "player.hpp"

using namespace std;

class Villager_G : public Player{
public:
	Villager_G(string name);
	virtual void day_died();
	virtual bool is_mafia();
	virtual void handle_kill();
protected:
};

#endif