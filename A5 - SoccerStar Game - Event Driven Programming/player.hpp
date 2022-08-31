#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
//#include "ball.hpp"
#include "RSDL/src/rsdl.hpp"

using namespace std;

class Player{
public:
	Rectangle get_rectangle();
	void change_coordinate(double i, double j);
	void change_velocity(double vx, double vy);
	void change_radius_and_speed(double radius, double m);
	void set_speed_zero();
	bool is_player_stopped();
	double get_x();
	double get_y();
	double get_V_x();
	double get_V_y();
	double get_radius();
	double get_mass();
	void move_one_step(double dt);
	bool is_selected(Point mouse_position);
private:
	double mass;
	double x;
	double y;
	double player_radius;
	double V_x;
	double V_y;
};

#endif