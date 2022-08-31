#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <exception>
#include <iostream>

class User_not_joined : public exception{
public:
const char* what() const noexcept{ return "User not joined\n"; }
};

class No_game_created : public exception{
public:
const char* what() const noexcept{ return "No game created\n"; }
};

class One_or_more_players_do_not_have_a_role : public exception{
public:
const char* what() const noexcept{ return "One or more players do not have a role\n"; }
};

class Game_has_already_started : public exception{
public:
const char* what() const noexcept{ return "Game has already started\n"; }
};

class Voter_is_silenced : public exception{
public:
const char* what() const noexcept{ return "Voter is silenced\n"; }
};

class Votee_already_dead : public exception{
public:
const char* what() const noexcept{ return "Votee already dead\n"; }
};

class User_can_not_wake_up_during_night : public exception{
public:
const char* what() const noexcept{ return "User can not wake up during night\n"; }
};

class User_is_dead : public exception{
public:
const char* what() const noexcept{ return "User is dead\n"; }
};

class Person_is_dead : public exception{
public:
const char* what() const noexcept{ return "Person is dead\n"; }
};

class Detective_has_already_asked : public exception{
public:
const char* what() const noexcept{ return "Detective has already asked\n"; }
};

class Suspect_is_dead : public exception{
public:
const char* what() const noexcept{ return "Suspect is dead\n"; }
};

class Doctor_has_already_healed : public exception{
public:
const char* what() const noexcept{ return "Doctor has already healed\n"; }
};

class Patient_is_dead : public exception{
public:
const char* what() const noexcept{ return "Patient is dead\n"; }
};

class Characters_already_swapped : public exception{
public:
const char* what() const noexcept{ return "Characters already swapped\n"; }
};

class Cant_swap_before_end_of_night : public exception{
public:
const char* what() const noexcept{ return "Can't swap before end of night\n"; }
};

class Voting_in_progress : public exception{
public:
const char* what() const noexcept{ return "Voting in progress\n"; }
};


#endif