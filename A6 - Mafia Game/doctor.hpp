#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "villager_G.hpp"
#include "exceptions.hpp"

using namespace std;

class Doctor : public Villager_G{
public:
	Doctor(string name);
	virtual void do_task(Player* votee);
private:

};



#endif