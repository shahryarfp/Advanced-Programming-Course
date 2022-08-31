#include "ball.hpp"
#include <iostream>
#include <cmath>
#include "RSDL/src/rsdl.hpp"
#define FRICTION_ACCELERATION 300.0

using namespace std;

double Ball::get_x(){
	return x;
}

double Ball::get_y(){
	return y;
}
double Ball::get_V_x(){
	return V_x;
}
double Ball::get_V_y(){
	return V_y;
}
double Ball::get_radius(){
	return ball_radius;
}
double Ball::get_mass(){
	return mass;
}
void Ball::change_radius_and_mass(double radius, double ball_mass){
	ball_radius = radius;
	mass = ball_mass;
}

void Ball::change_coordinate(double i, double j){
	x = i;
	y = j;
}
void Ball::change_velocity(double vx, double vy){
	V_x = vx;
	V_y = vy;
}
void Ball::set_speed_zero(){
	V_x = 0;
	V_y = 0;
}
Rectangle Ball::get_rectangle(){
	int first_element = (int)(x - ball_radius);
	double second_element = (int)(y - ball_radius + 50);
	return Rectangle(first_element, second_element, 2*ball_radius, 2*ball_radius);
}
bool Ball::is_goal(int table_width, int table_height){
	if(x < (ball_radius + 9) && y > (table_height / 3 + ball_radius) &&
	 y < (table_height * 2 / 3 - ball_radius) && V_x < 0){
		return true;
	}
	if(x > (table_width - ball_radius - 9) && y > (table_height / 3 + ball_radius) &&
	 y < (table_height * 2 / 3 - ball_radius) && V_x > 0){
		return true;
	}
	else
		return false;
}
int Ball::find_which_team_scored(int table_width, int table_height){
	if(x < (ball_radius + 9) && y > (table_height / 3 + ball_radius) &&
	 y < (table_height * 2 / 3 - ball_radius) && V_x < 0){
		return 2;
	}
	if(x > (table_width - ball_radius - 9) && y > (table_height / 3 + ball_radius) &&
	 y < (table_height * 2 / 3 - ball_radius) && V_x > 0){
		return 1;
	}
	else
		return 0;
}
double Ball::find_velocity(){
	double velocity_magnitude = sqrt(pow(V_x,2)+pow(V_y,2));
	return velocity_magnitude;
}
void Ball::move_one_step(double dt){
	//cout<<sqrt(pow(V_x, 2) + pow(V_y, 2))<<"hhhh"<<endl;
	double velocity_magnitude = sqrt(pow(V_x, 2) + pow(V_y, 2));
	//cout<<velocity_magnitude<<"hhhhhhh"<<endl;
	double new_magnitude = velocity_magnitude - (FRICTION_ACCELERATION * dt);
	if(velocity_magnitude != 0){
		V_x = (new_magnitude / velocity_magnitude) * V_x;
		V_y = (new_magnitude / velocity_magnitude) * V_y;
	}
	//cout<<point.x<<V_x<<dt<<endl;

	x = x + V_x * dt;
	y = y + V_y * dt;

	//cout<<point.x;

	if(V_x < 2 && V_x > -2)
		V_x = 0;
	if(V_y < 2 && V_y > -2)
		V_y = 0;
}