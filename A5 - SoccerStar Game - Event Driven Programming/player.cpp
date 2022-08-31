#include <iostream>
#include "player.hpp"
#include <cmath>
#define FRICTION_ACCELERATION 300.0

using namespace std;

double Player::get_x(){
	return x;
}
double Player::get_y(){
	return y;
}
double Player::get_V_x(){
	return V_x;
}
double Player::get_V_y(){
	return V_y;
}
double Player::get_radius(){
	return player_radius;
}
double Player::get_mass(){
	return mass;
}
void Player::change_coordinate(double i, double j){
	x = i;
	y = j;
}
void Player::change_velocity(double vx, double vy){
	V_x = vx;
	V_y = vy;
}
void Player::change_radius_and_speed(double radius, double m){
	player_radius = radius;
	mass = m;
}
void Player::set_speed_zero(){
	V_x = 0;
	V_y = 0;
}
Rectangle Player::get_rectangle(){
	int first_element = (int)(x - player_radius);
	int second_element = (int)(y - player_radius + 50);
	return Rectangle(first_element, second_element, 2*player_radius, 2*player_radius);
}
bool Player::is_player_stopped(){
	double velocity = sqrt(pow(V_x,2)+pow(V_y,2));
	if(velocity == 0){
		return true;
	}
	else
		return false;
}

void Player::move_one_step(double dt){

	double velocity_magnitude = sqrt(pow(V_x,2)+pow(V_y,2));
	double new_magnitude = velocity_magnitude - (FRICTION_ACCELERATION * dt);
	if(velocity_magnitude != 0){
		V_x = (new_magnitude / velocity_magnitude) * V_x;
		V_y = (new_magnitude / velocity_magnitude) * V_y;
	}
	x = x + V_x * dt;
	y = y + V_y * dt;
	
	if(V_x < 2 && V_x > -2)
		V_x = 0;
	if(V_y < 2 && V_y > -2)
		V_y = 0;
}

bool Player::is_selected(Point mouse_position){
	if(sqrt(pow(mouse_position.x - x, 2) + pow(mouse_position.y - 50 - y, 2)) < player_radius){
		return true;
	}
	else
		return false;
}