#include "likefilter.hpp"
#include <iostream>

vector<Song> Likefilter::apply_filter(vector<Song> song_list, string data1, string data2){
	if(stoi(data2) < stoi(data1) || stoi(data1) < 0 || stoi(data2) < 0)
		throw Bad_Request();
	vector<Song> like_filtered;
	for(int i=0; i<song_list.size(); i++){
		if(song_list[i].get_num_of_likes() >= stoi(data1) 
			&& song_list[i].get_num_of_likes() <= stoi(data2)){

			like_filtered.push_back(song_list[i]);
		}
	}
	return like_filtered;
}