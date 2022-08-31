#include "player.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Player::Player(string s){
	name = s;
	alive = true;
	silenced = false;
	status = "empty";
	night_task_done = false;
	healed = false;
}
bool Player::is_night_task_done(){return night_task_done;}
bool Player::is_silenced(){return silenced;}
bool Player::is_alive(){return alive;}
bool Player::is_healed(){return healed;}
string Player::get_name(){return name;}
string Player::get_status(){return status;}
void Player::silence(){silenced = true;}
void Player::heal(){healed = true;}
void Player::change_name(string s){name = s;}
void Player::change_silenced(bool b){silenced = b;}
void Player::reset_night_state(){
	night_task_done = false;
	healed = false;
	silenced = false;
}