#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>

using namespace std;

class Player{
public:
	Player(string s);
	virtual void day_died(){}
	virtual void do_task(Player* player){}
	virtual bool is_mafia(){return false;}
	virtual void handle_kill(){}
	bool is_healed();
	void heal();
	string get_name();
	bool is_silenced();
	bool is_alive();
	bool is_night_task_done();
	string get_status();
	void silence();
	void change_name(string s);
	void change_silenced(bool b);
	void reset_night_state();

protected:
	bool night_task_done;
	string name;
	bool alive;
	bool silenced;
	bool healed;
	string status;
};

#endif