#ifndef LIKEFILTER_HPP
#define LIKEFILTER_HPP

#include <iostream>
#include <vector>
#include "filter.hpp"
#include "exceptions.hpp"
using namespace std;

class Likefilter : public Filter{
public:
	virtual vector<Song> apply_filter(vector<Song> song_list, string data1, string data2);
private:
	
};



#endif