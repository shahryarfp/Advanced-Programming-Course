#include "silencer.hpp"
#include <iostream>
#include <cmath>


using namespace std;
Silencer::Silencer(string name)
	:Mafia_G(name)
{

}

void Silencer::do_task(Player* votee){
	if(!votee->is_alive()){
		throw Person_is_dead();
	}
	if(!night_task_done){
		votee->silence();
		night_task_done = true;
	}
}