#ifndef YEARFILTER_HPP
#define YEARFILTER_HPP

#include <iostream>
#include <vector>
#include "filter.hpp"
#include "exceptions.hpp"
using namespace std;

class Yearfilter : public Filter{
public:
	virtual vector<Song> apply_filter(vector<Song> song_list, string data1, string data2);
private:
	
};



#endif