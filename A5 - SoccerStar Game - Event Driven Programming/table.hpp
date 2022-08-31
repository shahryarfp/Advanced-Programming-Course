#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <vector>
#include "ball.hpp"
#include "RSDL/src/rsdl.hpp"
#include "player.hpp"

using namespace std;

class Table{
public:
	Table(double w, double h, double ball_radius,
 double players_radius, double ball_mass, double players_mass);
	bool is_all_win_A(int num_of_rounds);
	bool is_round_win_A(int num_of_goals);
	bool is_all_win_B(int num_of_rounds);
	bool is_round_win_B(int num_of_goals);
	bool is_goal_and_handle(bool& had_movement);
	bool are_all_stopped(bool& action);
	double find_ball_coordinate_x();
	double find_ball_coordinate_y();
	double get_height();
	double get_width();
	void change_player_velocity(Point mouse_position, int selected_player);
	void set_players_position();
	void move_one_step(double dt);
	void draw_velocity_vector(Window *window, Table& table, int selected_player,
	 Point mouse_position, int num_of_goals, int num_of_rounds);
	int find_selected_player(Point mouse_position);
	Rectangle find_ball_rectangle();
	Rectangle find_field_rectangle();
	Rectangle find_player_rectangle(int player_number);
	vector<int> get_scores();
	vector<double> reflect_round_objects_help(double& first_V_x,double& first_V_y,
		double& first_x,double& first_y,double& first_mass,double& second_V_x,
		double& second_V_y,double& second_x,double& second_y,double& second_mass, double dt);

private:
	bool is_no_contact();
	void reflect_object_with_table(double& x, double& y, double& V_x,
	double& V_y, double object_radius);
	bool contains_point(double x, double y, double object_radius);
	void reflect_ball_with_table();
	void reflect_player_with_table();
	void reflect_ball_with_player(double dt);
	void reflect_player_with_player(double dt);

	double width;
	double height;
	Ball ball;
	vector<Player> players;
	int round_A;
	int goal_A;
	int round_B;
	int goal_B;
	int turn_to_play;
};



#endif