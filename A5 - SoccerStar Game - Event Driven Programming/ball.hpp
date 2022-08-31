#ifndef BALL_HPP
#define BALL_HPP
#include "RSDL/src/rsdl.hpp"

class Ball{
public:
	void change_radius_and_mass(double radius, double ball_mass);
	void change_coordinate(double i, double j);
	void change_velocity(double vx, double vy);
	void set_speed_zero();
	bool is_goal(int table_width, int table_height);
	int find_which_team_scored(int table_width, int table_height);
	Rectangle get_rectangle();
	double find_velocity();
	double get_x();
	double get_y();
	void move_one_step(double dt);
	double get_V_x();
	double get_V_y();
	double get_radius();
	double get_mass();

private:
	double mass;
	double x;
	double y;
	double ball_radius;
	double V_x;
	double V_y;
};

#endif