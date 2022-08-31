#include "functions.hpp"
#include "RSDL/src/rsdl.hpp"
#include <iostream>
#include <string>
#include "table.hpp"

#define GAME_NAME "Soccer Stars"
#define MAX_SPEED_RADIUS 70
#define MAX_SPEED 800
#define dt 0.01

using namespace std;
bool is_number(string s){
	for(int i=0; i<s.length(); i++)
		if(isdigit(s[i]) == false)
			return false;
	
	return true;
}
int get_input(string gs){
	while(true){
		cout << "please enter " << gs << ": " << endl;
		string input;
		cin >> input;
		if(is_number(input))
			if(stoi(input) > 0)
				return stoi(input);

		cout << "wrong input!" << endl;
	}
}
void draw_field(Window *window,Table table){
	window->draw_img("Assets/field.jpg", table.find_field_rectangle(), NULL_RECT, 0, false, false);
}

void draw_ball(Window *window,Table table){
	window->draw_img("Assets/ball.png", table.find_ball_rectangle(), NULL_RECT, 0, false, false);
}

void draw_players(Window *window,Table table){
	for(int i=0; i<10; i++){
		if(i<5)
			window->draw_img("Assets/Player1.png", table.find_player_rectangle(i), NULL_RECT, 0, false, false);
		else
			window->draw_img("Assets/Player2.png", table.find_player_rectangle(i), NULL_RECT, 0, false, false);
	}
}
bool is_any_team_all_win(Table& table, int num_of_rounds){
	return table.is_all_win_A(num_of_rounds) || table.is_all_win_B(num_of_rounds);
}
bool is_any_team_round_win(Table& table,
 int num_of_goals, Window *window, int num_of_rounds){
	if(table.is_round_win_A(num_of_goals) || table.is_round_win_B(num_of_goals)){
		draw(window, table, num_of_goals, num_of_rounds);
		return true;
	}
	else
		return false;
}

void show_the_winner(Window *window,Table table, int num_of_rounds){
	
	cout<<"finished!!"<<endl;
	if(table.is_all_win_A(num_of_rounds)){
		window->show_text("Green won!!!", Point(220,235),
		 WHITE, "times new roman.ttf", 60);
	}
	else if(table.is_all_win_B(num_of_rounds)){
		window->show_text(" Red won!!!", Point(220,235),
		 WHITE, "times new roman.ttf", 60);
	}
	window->update_screen();
	while(true){
		while(window->has_pending_event()){
			Event event = window->poll_for_event();
			if(event.get_type() == Event::EventType::QUIT)
				exit(0);
		}
	}
}

void draw_rectangles_for_scores(Window *window){
	window->fill_rect(Rectangle(0,0,150,50), RGB(0, 50, 0));
	window->fill_rect(Rectangle(150,0,150,50), RGB(0, 85, 0));
	window->fill_rect(Rectangle(500,0,250,50), RGB(85, 0, 0));
	window->fill_rect(Rectangle(650,0,150,50), RGB(50, 0, 0));
	window->fill_rect(Rectangle(300,0,200,50), RGB(255, 255, 255));
	window->show_text(GAME_NAME, Point(311,5), BLACK, "times new roman.ttf", 33);
}
void show_scores(Window *window, Table table, int num_of_goals, int num_of_rounds){

	string rounds_A = "rounds: "+ to_string(table.get_scores()[0]) + '/' +
	 to_string((num_of_rounds+1)/2);
	window->show_text(rounds_A, Point(12,10), WHITE, "times new roman.ttf", 25);

	string goals_A = "goals: "+ to_string(table.get_scores()[1]) + '/' +
	 to_string(num_of_goals);
	window->show_text(goals_A, Point(165,10), WHITE, "times new roman.ttf", 25);

	string goals_B = "goals: "+ to_string(table.get_scores()[3]) + '/' +
	 to_string(num_of_goals);
	window->show_text(goals_B, Point(515,10), WHITE, "times new roman.ttf", 25);

	string rounds_B = "rounds: "+ to_string(table.get_scores()[2]) + '/' +
	 to_string((num_of_rounds+1)/2);
	window->show_text(rounds_B, Point(662,10), WHITE, "times new roman.ttf", 25);
}

void draw(Window *window,Table table, int num_of_goals, int num_of_rounds){
	window->clear();
	draw_field(window, table);
	draw_ball(window, table);
	draw_rectangles_for_scores(window);
	show_scores(window, table, num_of_goals, num_of_rounds);
	draw_players(window, table);
	window->update_screen();
}

void handle_mouse_input(Window *window, Table& table, int& selected_player,
 bool& action, bool& mouse_still_pressed, int num_of_goals,int num_of_rounds){
	while(window->has_pending_event()){
		Event event = window->poll_for_event();
		Point mouse_position;
		if(event.get_type() == Event::EventType::QUIT)
			exit(0);
		if(event.get_type() == Event::EventType::LCLICK){
			mouse_still_pressed = true;
			mouse_position = event.get_mouse_position();
			selected_player = table.find_selected_player(mouse_position);
			break;
		}
		if(event.get_type() == Event::EventType::LRELEASE && selected_player != -1){
			mouse_still_pressed = false;
			action = true;
			mouse_position = event.get_mouse_position();
			table.change_player_velocity(mouse_position, selected_player);
			break;
		}
		if(mouse_still_pressed){
			draw_field(window, table);
			draw_ball(window, table);
			draw_rectangles_for_scores(window);
			show_scores(window, table, num_of_goals, num_of_rounds);
			draw_players(window, table);
			mouse_position = get_current_mouse_position();
			table.draw_velocity_vector(window, table, selected_player,
			 mouse_position, num_of_goals, num_of_rounds);
		}
	}
}

void update(Window *window, Table& table){
	while(window->has_pending_event()){
		Event event = window->poll_for_event();
		if(event.get_type() == Event::EventType::QUIT)
			exit(0);
	}
	table.move_one_step(dt);
}

void handle_moves(Window *window,Table& table, 
	int num_of_goals, int num_of_rounds, bool& action){
	bool had_movement = false;
	while(!table.are_all_stopped(action) && !table.is_goal_and_handle(had_movement)){
		update(window, table);
		draw(window, table, num_of_goals, num_of_rounds);
		delay(15);
		had_movement = true;
	}
	if(had_movement)
		draw(window, table, num_of_goals, num_of_rounds);
}

void start_game(Window *window,Table& table, int& num_of_goals, int& num_of_rounds){
	draw(window, table, num_of_goals, num_of_rounds);
	while(!is_any_team_all_win(table, num_of_rounds)){
		int selected_player;
		bool action = false;
		bool mouse_still_pressed = false;
		while(!is_any_team_round_win(table, num_of_goals, window, num_of_rounds)){
			handle_mouse_input(window, table, selected_player,
			 action, mouse_still_pressed, num_of_goals, num_of_rounds);
			handle_moves(window,table, num_of_goals, num_of_rounds, action);
		}
	}
	draw(window, table, num_of_goals, num_of_rounds);
}