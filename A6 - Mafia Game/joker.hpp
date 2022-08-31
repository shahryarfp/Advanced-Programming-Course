#ifndef JOKER_HPP
#define JOKER_HPP

#include <iostream>
#include <vector>
#include "player.hpp"

using namespace std;

class Joker : public Player{
public:
	Joker(string name);
	virtual void day_died();
	virtual bool is_mafia();
	virtual void handle_kill();
private:

};



#endif