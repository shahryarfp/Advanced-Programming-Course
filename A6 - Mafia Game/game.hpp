#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <map>
#include "player.hpp"
#include "functions.hpp"
#include "exceptions.hpp"

#include "joker.hpp"

#include "mafia_G.hpp"
#include "mafia.hpp"
#include "godfather.hpp"
#include "silencer.hpp"

#include "villager_G.hpp"
#include "villager.hpp"
#include "detective.hpp"
#include "doctor.hpp"
#include "bulletproof.hpp"

class Game{
public:
	Game();
	void handle_command(string command);
private:
	void reset_game();
	void handle_create_game(vector<string> commands_in_line);
	void handle_assign_role(vector<string> commands_in_line);
	void handle_start_game(vector<string> commands_in_line);
	void handle_votes_in_day(vector<string> commands_in_line);
	void handle_tasks_at_night(vector<string> commands_in_line);
	void check_joined_user(vector<string> commands_in_line);
	void handle_mafia_vote(vector<string> commands_in_line);
	void handle_tasks(vector<string> commands_in_line);
	void handle_end_night(vector<string> commands_in_line);
	void handle_swap_character(vector<string> commands_in_line);
	void check_day_votes_throws(vector<string> commands_in_line);
	void check_night_tasks_throws(vector<string> commands_in_line);
	void handle_end_vote(vector<string> commands_in_line);
	void check_dead_players(vector<string> commands_in_line);
	void check_swap_throws(vector<string> commands_in_line);
	void change_characters(vector<string> commands_in_line);
	void handle_get_game_state(vector<string> commands_in_line);
	void print_start_game_messages();
	void check_end_game();
	void handle_start_night_messages();
	void handle_end_night_messages_and_kill();
	void check_start_game_throws();
	vector<Votes_help> ordering_votes();
	string find_result_vote(vector<Votes_help> ordered_votes);

	vector<Enrolled_Player> enrolled_players;
	vector<Player*> players;
	map<string,string> votes;
	bool is_game_started;
	bool is_game_created;
	bool can_swap;
	bool swapped;
	int day_num;
	int night_num;
	int num_of_villagers;
	int num_of_mafias;
	string mood;
};

#endif