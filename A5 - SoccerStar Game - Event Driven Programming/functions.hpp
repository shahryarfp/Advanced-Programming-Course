#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include "table.hpp"

using namespace std;
bool is_number(string s);
int get_input(string gs);
bool is_any_team_all_win(Table& table, int num_of_rounds);
bool is_any_team_round_win(Table& table, int num_of_goals,
 Window *window, int num_of_rounds);
void draw_field(Window *window,Table table);
void draw_ball(Window *window,Table table);
void draw_players(Window *window,Table table);
void show_the_winner(Window *window,Table table, int num_of_rounds);
void draw_rectangles_for_scores(Window *window);
void show_scores(Window *window, Table table, int num_of_goals, int num_of_rounds);
void draw(Window *window,Table table, int num_of_goals, int num_of_rounds);
void handle_mouse_input(Window *window, Table& table, int& selected_player,
 bool& action, bool& mouse_still_pressed,int num_of_goals,int num_of_rounds);
void update(Window *window, Table& table);
void handle_moves(Window *window,Table& table, int num_of_goals, int num_of_rounds, bool& action);
void start_game(Window *window,Table& table, int& num_of_goals, int& num_of_rounds);
#endif