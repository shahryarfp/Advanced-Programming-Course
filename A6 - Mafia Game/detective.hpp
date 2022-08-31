#ifndef DETECTIVE_HPP
#define DETECTIVE_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "villager_G.hpp"
#include "exceptions.hpp"

using namespace std;

class Detective : public Villager_G{
public:
	Detective(string name);
	virtual void do_task(Player* votee);
private:

};



#endif