#ifndef FILTER_HPP
#define FILTER_HPP

#include <iostream>
#include <vector>
#include "song.hpp"

using namespace std;

class Filter{
public:
	virtual vector<Song> apply_filter(vector<Song> song_list,
	 string data1, string data2) = 0;
private:
	
};



#endif