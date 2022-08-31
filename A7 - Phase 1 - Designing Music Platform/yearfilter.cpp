#include "yearfilter.hpp"
#include <iostream>

vector<Song> Yearfilter::apply_filter(vector<Song> song_list, string data1, string data2){
	if(stoi(data2) < stoi(data1))
		throw Bad_Request();
	vector<Song> year_filtered;
	for(int i=0; i<song_list.size(); i++){
		if(song_list[i].get_released_year() >= stoi(data1) 
			&& song_list[i].get_released_year() <= stoi(data2)){

			year_filtered.push_back(song_list[i]);
		}
	}
	return year_filtered;
}