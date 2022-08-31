#include "doctor.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Doctor::Doctor(string name)
	:Villager_G(name)
{

}

void Doctor::do_task(Player* votee){
	if(Player::is_night_task_done())
		throw Doctor_has_already_healed();
	if(!votee->is_alive())
		throw Patient_is_dead();
	votee->heal();
	night_task_done = true;
}