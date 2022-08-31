#ifndef GODFATHER_HPP
#define GODFATHER_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "mafia_G.hpp"

using namespace std;

class Godfather : public Mafia_G{
public:
	Godfather(string name);
	virtual bool is_mafia();
private:
};



#endif