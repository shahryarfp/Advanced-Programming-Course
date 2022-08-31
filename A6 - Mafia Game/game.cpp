#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>

#define FIRST_ELEMENT 0
#define SECOND_ELEMENT 1
#define THIRD_ELEMENT 2
#define DEFAULT -1

using namespace std;

Game::Game(){
	is_game_started = false;
	is_game_created = false;
	num_of_villagers = 0;
	num_of_mafias = 0;
	day_num = 0;
	night_num = 0;
	mood = "empty";
	can_swap = false;
	swapped = false;
}
void Game::handle_command(string command){
	vector<string> commands_in_line;
	commands_in_line.clear();
	split_command_line(command, commands_in_line);
	handle_create_game(commands_in_line);
	try{
		handle_assign_role(commands_in_line);
		handle_start_game(commands_in_line);
		if(is_game_started){
			handle_votes_in_day(commands_in_line);
			handle_end_vote(commands_in_line);
			handle_tasks_at_night(commands_in_line);
			handle_end_night(commands_in_line);
			handle_swap_character(commands_in_line);
			handle_get_game_state(commands_in_line);
		}
	}catch(exception& ex){
		cout<< ex.what();
	}
}
void Game::handle_get_game_state(vector<string> commands_in_line){
	if(commands_in_line[FIRST_ELEMENT] == "get_game_state"){
		int alive_villagers = num_of_villagers;
		int alive_mafias = num_of_mafias;
		for(int i=0; i<players.size(); i++){
			if(players[i]->get_status() == "mafia died")
				alive_mafias--;
			if(players[i]->get_status() == "villager died")
				alive_villagers--;
		}
		cout << "Mafia = " << alive_mafias << endl;
		cout << "Villager = " << alive_villagers << endl;
	}
}
void Game::handle_swap_character(vector<string> commands_in_line){
	if(commands_in_line[FIRST_ELEMENT] == "swap_character"){
		check_swap_throws(commands_in_line);
		change_characters(commands_in_line);
		can_swap = false;
		swapped = true;
	}
}
void Game::change_characters(vector<string> commands_in_line){
	int first_char = -1;
	int second_char = -1;
	for(int i=0; i<enrolled_players.size(); i++){
		if(enrolled_players[i].name == commands_in_line[SECOND_ELEMENT])
			first_char = i;
		if(enrolled_players[i].name == commands_in_line[THIRD_ELEMENT])
			second_char = i;
	}
	string p_name;
	p_name = enrolled_players[first_char].name;
	enrolled_players[first_char].name = enrolled_players[second_char].name;
	enrolled_players[second_char].name = p_name;

	Enrolled_Player p;
	p = enrolled_players[first_char];
	enrolled_players[first_char] = enrolled_players[second_char];
	enrolled_players[second_char] = p;

	p_name = players[first_char]->get_name();
	players[first_char]->change_name(players[second_char]->get_name());
	players[second_char]->change_name(p_name);

	bool b;
	b = players[first_char]->is_silenced();
	players[first_char]->change_silenced(players[second_char]->is_silenced());
	players[second_char]->change_silenced(b);

	Player* pp;
	pp = players[first_char];
	players[first_char] = players[second_char];
	players[second_char] = pp;
}

void Game::check_swap_throws(vector<string> commands_in_line){
	check_joined_user(commands_in_line);
	check_dead_players(commands_in_line);
	if(swapped){
		throw Characters_already_swapped();
	}
	if(mood == "night"){
		throw Cant_swap_before_end_of_night();
	}
	if(!can_swap){
		throw Voting_in_progress();
	}
}
void Game::check_dead_players(vector<string> commands_in_line){
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_name() == commands_in_line[SECOND_ELEMENT] 
			|| players[i]->get_name() == commands_in_line[THIRD_ELEMENT]){
			if(!players[i]->is_alive())
				throw User_is_dead();
		}
	}
}

void Game::handle_end_night(vector<string> commands_in_line){
	if(commands_in_line.size() ==1 && mood == "night" && 
		commands_in_line[FIRST_ELEMENT] == "end_night"){
		day_num++;
		handle_end_night_messages_and_kill();
		check_end_game();
		if(!is_game_created){
			return;
		}
		can_swap = true;
		swapped = false;
		mood = "day";
		votes.clear();
	}
}

bool compare_alphabetically(string player1, string player2){
	return player1 < player2;
}
vector<string> sort_alphabetically(vector<string> silenced_players){
	sort(silenced_players.begin(), silenced_players.end(), compare_alphabetically);
	return silenced_players;
}

void Game::handle_end_night_messages_and_kill(){
	vector<Votes_help> ordered_votes = ordering_votes();
	string vote_result = find_result_vote(ordered_votes);		
	cout << "Mafia tried to kill " << vote_result << endl;
	cout << "Day " << day_num << endl;
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_name() == vote_result && !players[i]->is_healed()){
			players[i]->handle_kill();
			break;
		}
	}
	vector<string> silenced_players;
	silenced_players.clear();
	for(int i=0; i<players.size(); i++){
		if(players[i]->is_silenced() && players[i]->is_alive()){
			silenced_players.push_back(players[i]->get_name());
		}
	}
	silenced_players = sort_alphabetically(silenced_players);
	if(silenced_players.size() >= 1){
		cout << "Silenced ";
		for(int i=0; i<silenced_players.size() - 1; i++){
			cout << silenced_players[i] << " ";
		}
		cout << silenced_players[silenced_players.size() - 1] << endl;
	}
}

void Game::handle_tasks_at_night(vector<string> commands_in_line){
	if(commands_in_line.size() == 2 && mood == "night"){
		check_night_tasks_throws(commands_in_line);
		check_joined_user(commands_in_line);
		handle_mafia_vote(commands_in_line);
		handle_tasks(commands_in_line);
	}
}

void Game::handle_tasks(vector<string> commands_in_line){
	int votee = DEFAULT;
	for(int i=0; i<players.size(); i++){
		if(commands_in_line[SECOND_ELEMENT] == players[i]->get_name()){
			votee = i;
		}
	}
	for(int i=0; i<enrolled_players.size(); i++){
		if(enrolled_players[i].name == commands_in_line[FIRST_ELEMENT]){
			for(int j=0; j<players.size(); j++){
				string role_ = enrolled_players[i].role;
				if(commands_in_line[0] == players[j]->get_name()){
					if(role_ == "detective" || role_ == "doctor" 
						|| role_ == "silencer"){
						players[j]->do_task(players[votee]);
						return;
					}
				}
			}
		}
	}
}

void Game::handle_mafia_vote(vector<string> commands_in_line){
	int voter = DEFAULT;
	for(int i=0; i<players.size(); i++){
		if(commands_in_line[0] == players[i]->get_name()){
			voter = i;
		}
	}
	bool votee_is_dead = false;
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_name() == commands_in_line[1] && !players[i]->is_alive()){
			votee_is_dead = true;
		}
	}
	for(int i=0; i<enrolled_players.size(); i++){
		if(enrolled_players[i].name == commands_in_line[FIRST_ELEMENT]){
			string role_ = enrolled_players[i].role;
			if(role_ == "godfather" || role_ == "mafia"){
				if(votee_is_dead)
					throw Votee_already_dead();
				string key = commands_in_line[FIRST_ELEMENT];
				votes[key] = commands_in_line[SECOND_ELEMENT]; 
				return;
			}
			if(role_ == "silencer" && players[voter]->is_night_task_done()){
				if(votee_is_dead)
					throw Votee_already_dead();
				string key = commands_in_line[FIRST_ELEMENT];
				votes[key] = commands_in_line[SECOND_ELEMENT]; 
				return;
			}
		}
	}
}

void Game::check_joined_user(vector<string> commands_in_line){
	int is_users_joined = 0;
	for(int i=0; i<players.size(); i++){
		if(commands_in_line[FIRST_ELEMENT] == players[i]->get_name())
			is_users_joined++;
		if(commands_in_line[SECOND_ELEMENT] == players[i]->get_name())
			is_users_joined++;
	}
	
	if(commands_in_line.size() == 2 && is_users_joined < 2)
		throw User_not_joined();
}
void Game::check_night_tasks_throws(vector<string> commands_in_line){
	for(int i=0; i<enrolled_players.size(); i++){
		if(enrolled_players[i].name == commands_in_line[FIRST_ELEMENT]){
			for(int j=0; j<players.size(); j++){
				if(enrolled_players[i].name == players[j]->get_name()){
					string role_ = enrolled_players[i].role;
					if(role_ == "joker" || role_ == "villager"
					 || role_ == "bulletproof"){
				 		throw User_can_not_wake_up_during_night();
					}
					if(!players[j]->is_alive()){
						throw User_is_dead();
					}
				}
			}
		}
	}
}
void Game::handle_end_vote(vector<string> commands_in_line){
	if(mood == "day" && commands_in_line[0] == "end_vote"){
		vector<Votes_help> ordered_votes = ordering_votes();

		if(ordered_votes.size() >= 1){
			string vote_result = find_result_vote(ordered_votes);
			for(int i=0; i<players.size(); i++){
				if(players[i]->get_name() == vote_result){
					players[i]->day_died();
					break;
				}
			}
		}
		check_end_game();
		if(!is_game_created){
			return;
		}
		night_num++;
		handle_start_night_messages();
		mood = "night";
		votes.clear();
		for(int i=0; i<players.size(); i++){
			players[i]->reset_night_state();
		}
	}
}
void Game::handle_start_night_messages(){
	cout << "Night " << night_num << endl;
	for(int i=0; i<enrolled_players.size(); i++){
		for(int j=0; j<players.size(); j++){
			if(enrolled_players[i].name == players[j]->get_name() && players[j]->is_alive()){
				string role_ = enrolled_players[i].role;
				if(role_ == "doctor" || role_ == "mafia" || role_ == "silencer" || 
					role_ == "godfather"||role_ == "detective"){
				 	
				 	cout << enrolled_players[i].name << ": ";
				 	cout << role_ << endl;
				 }
			}
		}
	}
}
void Game::check_end_game(){
	int alive_villagers = num_of_villagers;
	int alive_mafias = num_of_mafias;
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_status() == "Joker won"){
			cout << "Joker won";
			reset_game();
			return;
		}
		if(players[i]->get_status() == "mafia died")
			alive_mafias--;
		if(players[i]->get_status() == "villager died")
			alive_villagers--;
	}
	if(alive_mafias == 0){
		cout << "Villagers won";
		reset_game();
		return;
	}
	if(alive_villagers <= alive_mafias){
		cout << "Mafia won";
		reset_game();
		return;
	}
}
string Game::find_result_vote(vector<Votes_help> ordered_votes){
	string vote_result;
	vote_result = ordered_votes[FIRST_ELEMENT].name;
	for(int i=0; i<ordered_votes.size()-1; i++){
		if(ordered_votes[i].num_of_votes < ordered_votes[i+1].num_of_votes){
			vote_result = ordered_votes[i+1].name;
		}
		if(ordered_votes[i].num_of_votes == ordered_votes[i+1].num_of_votes && 
			ordered_votes[i].name > ordered_votes[i+1].name){
			vote_result = ordered_votes[i+1].name;
		}
	}
	return vote_result;
}
vector<Votes_help> Game::ordering_votes(){
	vector<Votes_help> votes_help;
	bool user_found;
	for(const auto &p : votes){
		user_found = false;
		for(int i=0; i<votes_help.size(); i++){
			if(votes_help[i].name == p.second){
				votes_help[i].num_of_votes++;
				user_found = true;
				break;
			}
		}
		if(!user_found){
			Votes_help vote_;
			vote_.name = p.second;
			vote_.num_of_votes = 1;
			votes_help.push_back(vote_);
		}
	}
	return votes_help;
}
void Game::handle_votes_in_day(vector<string> commands_in_line){
	if(commands_in_line.size() == 2 && mood == "day"){
		check_day_votes_throws(commands_in_line);
		can_swap = false;
		swapped = false;
		string key = commands_in_line[0];
		votes[key] = commands_in_line[1]; 
	}
}

void Game::check_day_votes_throws(vector<string> commands_in_line){
	int is_users_joined = 0;
	for(int i=0; i<players.size(); i++){
		if(commands_in_line[FIRST_ELEMENT] == players[i]->get_name())
			is_users_joined++;
		if(commands_in_line[SECOND_ELEMENT] == players[i]->get_name())
			is_users_joined++;
	}
	if(commands_in_line.size() == 2 && is_users_joined < 2)
		throw User_not_joined();
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_name() == commands_in_line[FIRST_ELEMENT] && players[i]->is_silenced())
			throw Voter_is_silenced();
	}
	for(int i=0; i<players.size(); i++){
		if(players[i]->get_name() == commands_in_line[SECOND_ELEMENT] && !players[i]->is_alive())
			throw Votee_already_dead();
	}
}

void Game::handle_create_game(vector<string> commands_in_line){
	if(commands_in_line.size() > 1 && commands_in_line[FIRST_ELEMENT] == "create_game"){
		reset_game();
		is_game_created = true;
		for(int i=1; i<commands_in_line.size(); i++){
			Enrolled_Player enrolled_player;
			enrolled_player.name = commands_in_line[i];
			enrolled_player.role = "no role";
			enrolled_players.push_back(enrolled_player);
		}
	}
}

void Game::handle_assign_role(vector<string> commands_in_line){
	if(commands_in_line.size() == 3 && commands_in_line[FIRST_ELEMENT] == "assign_role"){
		if(is_game_created == false)
			throw No_game_created();

		bool was_player_found = false;
		for(int i=0; i<enrolled_players.size(); i++){
			if(enrolled_players[i].name == commands_in_line[SECOND_ELEMENT]){
				enrolled_players[i].role = commands_in_line[THIRD_ELEMENT];
				was_player_found = true;
			}
		}
		if(was_player_found == false)
			throw User_not_joined();
	}
}

void Game::handle_start_game(vector<string> commands_in_line){
	if(commands_in_line.size() == 1 && commands_in_line[FIRST_ELEMENT] == "start_game"){
		check_start_game_throws();
		is_game_started = true;
		for(int i=0; i<enrolled_players.size(); i++){
			if(enrolled_players[i].role == "joker"){
				Joker* joker = new Joker(enrolled_players[i].name);
				players.push_back(joker);
			}
			if(enrolled_players[i].role == "mafia"){
				Mafia* mafia = new Mafia(enrolled_players[i].name);
				num_of_mafias++;
				players.push_back(mafia);
			}
			if(enrolled_players[i].role == "godfather"){
				Godfather* godfather = new Godfather(enrolled_players[i].name);
				num_of_mafias++;
				players.push_back(godfather);
			}
			if(enrolled_players[i].role == "silencer"){
				Silencer* silencer = new Silencer(enrolled_players[i].name);
				num_of_mafias++;
				players.push_back(silencer);
			}
			if(enrolled_players[i].role == "villager"){
				Villager* villager = new Villager(enrolled_players[i].name);
				num_of_villagers++;
				players.push_back(villager);
			}
			if(enrolled_players[i].role == "detective"){
				Detective* detective = new Detective(enrolled_players[i].name);
				num_of_villagers++;
				players.push_back(detective);
			}
			if(enrolled_players[i].role == "doctor"){
				Doctor* doctor = new Doctor(enrolled_players[i].name);
				num_of_villagers++;
				players.push_back(doctor);
			}
			if(enrolled_players[i].role == "bulletproof"){
				Bulletproof* bulletproof = new Bulletproof(enrolled_players[i].name);
				num_of_villagers++;
				players.push_back(bulletproof);
			}

		}
		print_start_game_messages();
		day_num++;
		cout << "Day " << day_num << endl;
		mood = "day";
	}
}	
	
void Game::print_start_game_messages(){
	for(int i=0; i<enrolled_players.size(); i++){
		cout << enrolled_players[i].name << ": ";
		cout << enrolled_players[i].role << endl;
	}
	cout << "Ready? Set! Go." << endl;
}

void Game::check_start_game_throws(){
	for(int i=0; i<enrolled_players.size(); i++){
		if(enrolled_players[i].role == "no role"){
			throw One_or_more_players_do_not_have_a_role();
		}
	}
	if(is_game_created == false)
		throw No_game_created();
	if(is_game_started == true)
		throw Game_has_already_started();
}

void Game::reset_game(){
	enrolled_players.clear();
	players.clear();
	votes.clear();
	mood = "empty";
	day_num = 0;
	night_num = 0;
	is_game_created = false;
	is_game_started = false;
	num_of_mafias = 0;
	num_of_villagers = 0;
	can_swap = false;
	swapped = false;
}
