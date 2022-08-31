#include "artistfilter.hpp"
#include <iostream>

vector<Song> Artistfilter::apply_filter(vector<Song> song_list, string data1, string data2){
	vector<Song> artist_filtered;
	for(int i=0; i<song_list.size(); i++){
		if(song_list[i].get_artist() == data1)
			artist_filtered.push_back(song_list[i]);
	}
	return artist_filtered;
}