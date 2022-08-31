#ifndef SILENCER_HPP
#define SILENCER_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "mafia_G.hpp"
#include "exceptions.hpp"

using namespace std;

class Silencer : public Mafia_G{
public:
	Silencer(string name);
	virtual void do_task(Player* votee);
private:

};


#endif