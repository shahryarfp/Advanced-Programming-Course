#include "detective.hpp"
#include <iostream>
#include <cmath>

using namespace std;
Detective::Detective(string name)
	:Villager_G(name)
{

}
void Detective::do_task(Player* votee){
	if(Player::is_night_task_done()){
		throw Detective_has_already_asked();
	}
	if(!votee->is_alive()){
		throw Suspect_is_dead();
	}
	if(votee->is_mafia())
		cout << "Yes\n";
	else
		cout << "No\n";

	night_task_done = true;
}