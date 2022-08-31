#include "table.hpp"
#include "RSDL/src/rsdl.hpp"
#include "functions.hpp"
#include <iostream>
#include <cmath>

#define INITIAL_ROUND_AND_GOAL 0
#define A_TURN -1
#define B_TURN 1
#define MAX_SPEED_RADIUS 130
#define MAX_SPEED 800
#define TEAM_A 1
#define TEAM_B 2

using namespace std;

double Table::get_height(){
	return height;
}

double Table::get_width(){
	return width;
}

double Table::find_ball_coordinate_x(){
	return ball.get_x();
}

double Table::find_ball_coordinate_y(){
	return ball.get_y();
}

Rectangle Table::find_ball_rectangle(){
	return ball.get_rectangle();
}

Rectangle Table::find_player_rectangle(int player_number){
	return players[player_number].get_rectangle();
}

Table::Table(double w, double h, double ball_radius, double players_radius, double ball_mass, double players_mass){
	width = w;
	height = h;
	round_A = INITIAL_ROUND_AND_GOAL;
	goal_A = INITIAL_ROUND_AND_GOAL;
	round_B = INITIAL_ROUND_AND_GOAL;
	goal_B = INITIAL_ROUND_AND_GOAL;
	turn_to_play = A_TURN;
	ball.change_coordinate(w / 2, h / 2);
	ball.change_radius_and_mass(ball_radius, ball_mass);
	ball.set_speed_zero();
	for(int i=0; i<10; i++){
		Player player;
		player.change_radius_and_speed(players_radius, players_mass);
		player.set_speed_zero();
		players.push_back(player);
	}
	set_players_position();
}

void Table::set_players_position(){
	players[0].change_coordinate(25,240);
	players[1].change_coordinate(160,120);
	players[2].change_coordinate(160,360);
	players[3].change_coordinate(300,180);
	players[4].change_coordinate(300,300);

	players[5].change_coordinate(775,240);
	players[6].change_coordinate(640,120);
	players[7].change_coordinate(640,360);
	players[8].change_coordinate(500,180);
	players[9].change_coordinate(500,300);
}

bool Table::contains_point(double x, double y, double object_radius){
	return x > object_radius && x < width - object_radius &&
	 y > object_radius && y < height - object_radius;
}

bool Table::is_all_win_A(int num_of_rounds){
	if(round_A == (num_of_rounds + 1) / 2)
		return true;
	else
		return false;
}
bool Table::is_all_win_B(int num_of_rounds){
	if(round_B == (num_of_rounds + 1) / 2)
		return true;
	else
		return false;
}
bool Table::is_round_win_A(int num_of_goals){
	if(goal_A == num_of_goals){
		turn_to_play = B_TURN;
		round_A++;
		goal_A = 0;
		return true;
	}
	else
		return false;
}
bool Table::is_round_win_B(int num_of_goals){
	if(goal_B == num_of_goals){
		turn_to_play = A_TURN;
		round_B++;
		goal_B = 0;
		return true;
	}
	else
		return false;
}
Rectangle Table::find_field_rectangle(){
	return Rectangle(0, 50, (int)width, (int)height);
}
bool Table::is_goal_and_handle(bool& had_movement){
	if(ball.is_goal(width, height)){
		int team_scored = ball.find_which_team_scored(width, height);
		if(team_scored == TEAM_A){
			turn_to_play = A_TURN;
			goal_A++;
		}
		else if(team_scored == TEAM_B){
			turn_to_play = B_TURN;
			goal_B++;
		}
		ball.set_speed_zero();
		ball.change_coordinate(width/2, height/2);

		for(int i=0; i<10; i++)
			players[i].set_speed_zero();

		set_players_position();
		had_movement = true;
		return true;
	}
	else
		return false;
}
bool Table::are_all_stopped(bool& action){
	for(int i=0; i<10 ; i++)
		if(!players[i].is_player_stopped())
			return false;

	if(ball.find_velocity() != 0)
		return false;

	if(action == true){
		turn_to_play = turn_to_play * (-1);
		action = false;
	}
	return true;
}
vector<int> Table::get_scores(){
	vector<int> scores;
	scores.push_back(round_A);
	scores.push_back(goal_A);
	scores.push_back(round_B);
	scores.push_back(goal_B);
	return scores;
}
void Table::reflect_object_with_table(double& x, double& y, double& V_x, double& V_y,
	double object_radius){
	if(x < object_radius){
		x = 2 * object_radius - x;
		V_x = -V_x;
	}
	if(x > width - object_radius){
		x = 2 * (width - object_radius) - x;
		V_x = -V_x;
	}
	if(y < object_radius){
		y = 2 * object_radius - y;
		V_y = -V_y;
	}
	if(y > (height - object_radius)){
		y = 2 * (height - object_radius) - y;
		V_y = -V_y;
	}
}
void Table::reflect_ball_with_table(){
	double V_x = ball.get_V_x();
	double V_y = ball.get_V_y();
	double x = ball.get_x();
	double y = ball.get_y();
	double ball_radius = ball.get_radius();
	reflect_object_with_table(x, y, V_x, V_y, ball_radius);
	ball.change_coordinate(x, y);
	ball.change_velocity(V_x, V_y);
}
void Table::reflect_player_with_table(){
	for(int i=0; i<10; i++){
		double V_x = players[i].get_V_x();
		double V_y = players[i].get_V_y();
		double x = players[i].get_x();
		double y = players[i].get_y();
		double player_radius = players[i].get_radius();
		reflect_object_with_table(x, y, V_x, V_y, player_radius);
		players[i].change_coordinate(x, y);
		players[i].change_velocity(V_x, V_y);
	}
}
vector<double> Table::reflect_round_objects_help(double& first_V_x,double& first_V_y,
	double& first_x,double& first_y,double& first_mass,double& second_V_x,
	double& second_V_y,double& second_x,double& second_y,double& second_mass, double dt){

	first_x = first_x - first_V_x * dt;
	first_y = first_y - first_V_y * dt;
	second_x = second_x - second_V_x * dt;
	second_y = second_y - second_V_y * dt;

	double first_V_x_new = first_V_x - 2*second_mass/(second_mass+first_mass)*
	((first_V_x - second_V_x)*(first_x- second_x)+(first_V_y - second_V_y)*(first_y- second_y))/
	(pow(first_x-second_x,2)+pow(first_y-second_y,2))*(first_x-second_x);

	double first_V_y_new = first_V_y - 2*second_mass/(second_mass+first_mass)*
	((first_V_x - second_V_x)*(first_x- second_x)+(first_V_y - second_V_y)*(first_y- second_y))/
	(pow(first_x-second_x,2)+pow(first_y-second_y,2))*(first_y-second_y);

	double second_V_x_new = second_V_x - 2*first_mass/(second_mass+first_mass)*
	((second_V_x - first_V_x)*(second_x- first_x)+(second_V_y - first_V_y)*(second_y- first_y))/
	(pow(first_x-second_x,2)+pow(first_y-second_y,2))*(second_x-first_x);

	double second_V_y_new = second_V_y - 2*first_mass/(second_mass+first_mass)*
	((second_V_x - first_V_x)*(second_x- first_x)+(second_V_y - first_V_y)*(second_y- first_y))/
	(pow(first_x-second_x,2)+pow(first_y-second_y,2))*(second_y-first_y);

	vector<double> new_velocity;
	new_velocity.push_back(first_V_x_new);
	new_velocity.push_back(first_V_y_new);
	new_velocity.push_back(second_V_x_new);
	new_velocity.push_back(second_V_y_new);
	return new_velocity;

}
void Table::reflect_ball_with_player(double dt){
	double b_V_x = ball.get_V_x();
	double b_V_y = ball.get_V_y();
	double b_x = ball.get_x();
	double b_y = ball.get_y();
	double b_radius = ball.get_radius();
	double b_mass = ball.get_mass();

	for(int i = 0; i < 10; i++){
		double p_V_x = players[i].get_V_x();
		double p_V_y = players[i].get_V_y();
		double p_x = players[i].get_x();
		double p_y = players[i].get_y();
		double p_radius = players[i].get_radius();
		double p_mass = players[i].get_mass();

		double center_distance = sqrt(pow(b_x-p_x,2) + pow(b_y-p_y,2));
		if(center_distance <= p_radius + b_radius){
			vector<double> new_velocity = reflect_round_objects_help(b_V_x,b_V_y,b_x,b_y,
			 b_mass,p_V_x,p_V_y,p_x,p_y,p_mass, dt);

			ball.change_coordinate(b_x, b_y);
			ball.change_velocity(new_velocity[0], new_velocity[1]);
			players[i].change_coordinate(p_x, p_y);
			players[i].change_velocity(new_velocity[2], new_velocity[3]);
		}
	}
}
void Table::reflect_player_with_player(double dt){
	for(int i=0; i<10; i++){
		int j = i + 1;
		while(j < 10){
			double b_V_x = players[i].get_V_x();
			double b_V_y = players[i].get_V_y();
			double b_x = players[i].get_x();
			double b_y = players[i].get_y();
			double b_mass = players[i].get_mass();

			double p_V_x = players[j].get_V_x();
			double p_V_y = players[j].get_V_y();
			double p_x = players[j].get_x();
			double p_y = players[j].get_y();
			double players_radius = players[j].get_radius();
			double p_mass = players[j].get_mass();
			
			double center_distance = sqrt(pow(b_x-p_x,2) + pow(b_y-p_y,2));
			if(center_distance <= 2 * players_radius){
				vector<double> new_velocity = reflect_round_objects_help(b_V_x,
					b_V_y,b_x,b_y,b_mass,p_V_x,p_V_y,p_x,p_y,p_mass, dt);

				players[i].change_coordinate(b_x, b_y);
				players[i].change_velocity(new_velocity[0], new_velocity[1]);
				players[j].change_coordinate(p_x, p_y);
				players[j].change_velocity(new_velocity[2], new_velocity[3]);
			}
			j++;
		}
	}
}
bool Table::is_no_contact(){
	if(!contains_point(ball.get_x(),ball.get_y(),ball.get_radius()))
		return false;

	double b_x = ball.get_x();
	double b_y = ball.get_y();
	double b_radius = ball.get_radius();

	for(int i=0; i<10; i++){
		double p_x = players[i].get_x();
		double p_y = players[i].get_y();
		double p_radius = players[i].get_radius();

		if(!contains_point(p_x, p_y, p_radius))
			return false;

		double center_distance = sqrt(pow(b_x-p_x,2) + pow(b_y-p_y,2));
		if(center_distance <= p_radius + b_radius)
			return false;
	}
	
	for(int i=0; i<10; i++){
		int j = i + 1;
		while(j < 10){
			double p_x = players[j].get_x();
			double p_y = players[j].get_y();
			double players_radius = players[j].get_radius();
			double b_x = players[i].get_x();
			double b_y = players[i].get_y();
			double center_distance = sqrt(pow(b_x-p_x,2) + pow(b_y-p_y,2));
			
			if(center_distance <= 2 * players_radius)
				return false;
			j++;
		}
	}

	return true;
}

void Table::move_one_step(double dt){
	ball.move_one_step(dt);
	for(int i = 0; i < 10; i++)
		players[i].move_one_step(dt);

	while(!is_no_contact()){
		reflect_ball_with_table();
		reflect_player_with_table();
		reflect_ball_with_player(dt);
		reflect_player_with_player(dt);
	}
}

int Table::find_selected_player(Point mouse_position){
	for(int i=0; i<10; i++){
		if(players[i].is_selected(mouse_position) && turn_to_play == A_TURN && i<5)
			return i;

		if(players[i].is_selected(mouse_position) && turn_to_play == B_TURN && i>4)
			return i;
	}
	return -1;
}
void Table::change_player_velocity(Point mouse_position, int selected_player){

	double player_x = players[selected_player].get_x();
	double player_y = players[selected_player].get_y();
	double mouse_and_player_distance = sqrt(pow(mouse_position.x - player_x, 2)
	 + pow(mouse_position.y - 50 - player_y, 2));
	
	double player_velocity;
	if(mouse_and_player_distance > MAX_SPEED_RADIUS)
		player_velocity = MAX_SPEED;
	else
		player_velocity = mouse_and_player_distance / MAX_SPEED_RADIUS * MAX_SPEED;

	double player_vx = (player_x - mouse_position.x) /
	 mouse_and_player_distance * player_velocity;

	double player_vy = (player_y - mouse_position.y + 50) /
	 mouse_and_player_distance * player_velocity;

	players[selected_player].change_velocity(player_vx, player_vy);
}

void Table::draw_velocity_vector(Window *window, Table& table, int selected_player,
 Point mouse_position, int num_of_goals, int num_of_rounds){

	double player_x = players[selected_player].get_x();
	double player_y = players[selected_player].get_y() + 50;
	bool selected_on_turn_A = selected_player < 5 && turn_to_play == A_TURN;
	bool selected_on_turn_B = selected_player > 5 && turn_to_play == B_TURN;
	if(selected_on_turn_A || selected_on_turn_B){
		
		Rectangle ring_rec = Rectangle(player_x- MAX_SPEED_RADIUS,
	 	player_y- MAX_SPEED_RADIUS, 2*MAX_SPEED_RADIUS, 2*MAX_SPEED_RADIUS );
		window->draw_img("Assets/ring.png", ring_rec, NULL_RECT, 0, false, false);

		draw_rectangles_for_scores(window);
		show_scores(window, table, num_of_goals, num_of_rounds);

		double mouse_and_player_distance = sqrt(pow(player_x-mouse_position.x ,2)
			+pow(player_y-mouse_position.y,2));
		if(mouse_and_player_distance > MAX_SPEED_RADIUS){
			
			Point player_center;
			player_center.x = (int)player_x;
			player_center.y = (int)player_y;
			Point dest;
			dest.x = 2*player_center.x - mouse_position.x;
			dest.y = 2*player_center.y - mouse_position.y;
			dest.x = (int)(player_center.x+(dest.x-player_center.x)
				*MAX_SPEED_RADIUS/mouse_and_player_distance);
			dest.y = (int)(player_center.y+(dest.y-player_center.y)
				*MAX_SPEED_RADIUS/mouse_and_player_distance);
			window->draw_line(player_center, dest, WHITE);
			window->update_screen();
			return;
		}
		Point player_center;
		player_center.x = (int)player_x;
		player_center.y = (int)player_y;
		Point dest;
		dest.x = (int)(2*player_center.x - mouse_position.x);
		dest.y = (int)(2*player_center.y - mouse_position.y);
		window->draw_line(player_center, dest, WHITE);
	}
	window->update_screen();
}