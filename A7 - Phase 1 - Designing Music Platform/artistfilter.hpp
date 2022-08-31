#ifndef ARTISTFILTER_HPP
#define ARTISTFILTER_HPP

#include <iostream>
#include <vector>
#include "filter.hpp"

using namespace std;

class Artistfilter : public Filter{
public:
	virtual vector<Song> apply_filter(vector<Song> song_list, string data1, string data2);
private:
	
};

#endif