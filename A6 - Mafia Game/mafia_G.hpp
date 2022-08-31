#ifndef MAFIA_G_HPP
#define MAFIA_G_HPP

#include <iostream>
#include <vector>
#include "player.hpp"

using namespace std;

class Mafia_G : public Player{
public:
	Mafia_G(string name);
	virtual void day_died();
	virtual bool is_mafia();
	virtual void handle_kill();
protected:

};



#endif