#include <iostream>
#include "table.hpp"
#include "RSDL/src/rsdl.hpp"
#include "functions.hpp"
#include <cmath>

#define GAME_NAME "Soccer Stars"
#define TABLE_WIDTH 800
#define TABLE_HEIGHT 480
#define BALL_RADIUS 12
#define PLAYERS_RADIUS 27
#define BALL_MASS 2
#define PLAYERS_MASS 5
#define SCORESBAR_WIDTH 50
#define dt 0.02

using namespace std;

int main(){

	int num_of_rounds = get_input("n");
	int num_of_goals = get_input("m");
	Window *window = new Window(TABLE_WIDTH,
	 TABLE_HEIGHT + SCORESBAR_WIDTH, GAME_NAME);
	Table table(TABLE_WIDTH, TABLE_HEIGHT, BALL_RADIUS,
	 PLAYERS_RADIUS, BALL_MASS, PLAYERS_MASS);

	start_game(window, table, num_of_goals, num_of_rounds);
	show_the_winner(window, table, num_of_rounds);
	return 0;
}