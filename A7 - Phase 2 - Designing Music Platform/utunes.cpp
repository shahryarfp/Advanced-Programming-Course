#include "utunes.hpp"
#include <iostream>

using namespace std;

#define NO_ONE -1;

Utunes::Utunes(vector<Song> songs_, vector<Liked_Song> liked_songs_){
	songs = songs_;
	add_liked_songs(liked_songs_);
	filtered_songs = songs_;
	enterd_user = NO_ONE;
	update_users_and_songs_matrix();
	update_similarity_matrix();
	filters["artist"] = " ";
	filters["year"] = " ";
	filters["like"] = " ";
}

string hash_string(string s){
	hash<string> hash;
	return to_string(hash(s));
}

void Utunes::add_liked_songs(vector<Liked_Song> liked_songs_){
	for(int i=0; i<liked_songs_.size(); i++){
		if(i>0 && liked_songs_[i].get_username() == liked_songs_[i-1].get_username())
			continue;
		string username = liked_songs_[i].get_username();
		string email = liked_songs_[i].get_email();
		string password = liked_songs_[i].get_password();
		password = hash_string(password);
		User new_user = User(email, username, password);
		users.push_back(new_user);
	}
	for(int i=0; i<liked_songs_.size(); i++){
		for(int j=0; j<users.size(); j++){
			if(users[j].get_username() == liked_songs_[i].get_username()){
				for(int k=0; k<songs.size(); k++){
					if(songs[k].get_id() == liked_songs_[i].get_liked_song()){
						users[j].add_initial_likes(&songs[k]);
					}
				}
			}
		}
	}
}


void Utunes::handle_command(string command){
	vector<string> commands_in_line = split_command_line(command);
	try{
		handle_throws(commands_in_line);
		handle_signup(commands_in_line);
		handle_login(commands_in_line);
		handle_logout(commands_in_line);
		handle_get_songs_list(commands_in_line);
		handle_get_song(commands_in_line);
		handle_like_song(commands_in_line);
		handle_get_likes(commands_in_line);
		handle_delete_likes(commands_in_line);
		handle_post_playlists(commands_in_line);
		handle_get_playlists(commands_in_line);
		handle_post_playlists_songs(commands_in_line);
		handle_get_playlists_songs(commands_in_line);
		handle_delete_playlists_songs(commands_in_line);
		handle_get_users(commands_in_line);
		handle_filters(commands_in_line);
		handle_delete_filters(commands_in_line);
		handle_post_comments(commands_in_line);
		handle_get_comments(commands_in_line);
		handle_similar_users(commands_in_line);
		handle_recommended(commands_in_line);
	}catch(exception& ex){
		cout<< ex.what();
	}
}

void Utunes::handle_signup(vector<string> commands_in_line){
	if(commands_in_line[1] != "signup")
		return;
	for(int i=0; i<users.size(); i++){
		if(users[i].get_email() == commands_in_line[4] 
			|| users[i].get_username() == commands_in_line[6]){
			throw Bad_Request();
		}
	}
	if(commands_in_line.size() != 9 || commands_in_line[5] != "username"
		|| commands_in_line[7] != "password" || commands_in_line[2] != "?"
		|| commands_in_line[3] != "email"){
		throw Bad_Request();
	}
	string pass = commands_in_line[8];
	pass = hash_string(pass);
	User new_user = User(commands_in_line[4],commands_in_line[6], pass);
	users.push_back(new_user);
	enterd_user = users.size() - 1;
	cout << "OK" << endl;
}

void Utunes::handle_login(vector<string> commands_in_line){
	if(commands_in_line[1] != "login")
		return;
	if(commands_in_line.size() != 7 || commands_in_line[3] != "email"
		|| commands_in_line[5] != "password" || commands_in_line[2] != "?"){
		throw Bad_Request();
	}
	bool user_found = false;
	int enterd_user_;
	for(int i=0; i<users.size(); i++){
		if(users[i].get_email() == commands_in_line[4] 
			&& users[i].get_password() == hash_string(commands_in_line[6])){
			user_found = true;
		enterd_user_ = i;
		}
	}
	if(!user_found)
		throw Bad_Request();
	enterd_user = enterd_user_;
	cout << "OK" << endl;
}

void Utunes::handle_logout(vector<string> commands_in_line){
	if(commands_in_line[1] != "logout")
		return;
	if(commands_in_line[0] != "POST"){
		throw Bad_Request();
	}
	enterd_user = NO_ONE;
	cout << "OK" << endl;
}

void Utunes::handle_get_songs_list(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "songs" 
		|| commands_in_line.size() > 2)
		return;
	if(filtered_songs.size() == 0)
		throw Empty();
	filtered_songs = sort_by_id(filtered_songs);
	for(int i=0; i<filtered_songs.size(); i++){
		cout << filtered_songs[i].get_id() << " ";
		cout << filtered_songs[i].get_title() << " ";
		cout << filtered_songs[i].get_artist() << " ";
		cout << filtered_songs[i].get_released_year() << endl;
	}
}

void Utunes::handle_get_song(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "songs"
	 || commands_in_line.size() < 3){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[2] != "?" 
		|| commands_in_line[3] != "id"){
		throw Bad_Request();
	}
	if(stoi(commands_in_line[4]) < 1 
		|| stoi(commands_in_line[4]) > songs.size()){
		throw Not_Found();
	}
	songs[stoi(commands_in_line[4])-1].print_info();
}

void Utunes::handle_like_song(vector<string> commands_in_line){
	if(commands_in_line[0] != "POST" || commands_in_line[1] != "likes"
	 || commands_in_line[2] != "?"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "id"){
		throw Bad_Request();
	}
	if(stoi(commands_in_line[4]) < 1 
		|| stoi(commands_in_line[4]) > songs.size()){
		throw Not_Found();
	}
	users[enterd_user].add_to_likes(&songs[stoi(commands_in_line[4])-1]);
}

void Utunes::handle_get_likes(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "likes" 
		|| commands_in_line.size() > 2)
		return;
	users[enterd_user].print_likes();
}

void Utunes::handle_delete_likes(vector<string> commands_in_line){
	if(commands_in_line[0] != "DELETE" || commands_in_line[1] != "likes"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "id"){
		throw Bad_Request();
	}
	if(stoi(commands_in_line[4])<1 || stoi(commands_in_line[4])>songs.size())
		throw Not_Found();
	users[enterd_user].delete_from_likes(&songs[stoi(commands_in_line[4])-1]);
}

void Utunes::handle_post_playlists(vector<string> commands_in_line){
	if(commands_in_line[0] != "POST" || commands_in_line[1] != "playlists"){
		return;
	}
	if(commands_in_line.size() != 7 || commands_in_line[3] != "name" 
		|| commands_in_line[5] != "privacy"){
		throw Bad_Request();
	}
	bool is_private;
	if(commands_in_line[6] == "private")
		is_private = true;
	else if(commands_in_line[6] == "public")
		is_private = false;
	string Playlist_name = commands_in_line[4];
	Playlist new_playlist = Playlist(Playlist_name, is_private,
	 playlists.size() + 1, users[enterd_user].get_username());
	playlists.push_back(new_playlist);
	cout << playlists.size() << endl;
}

void Utunes::handle_get_playlists(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "playlists"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "username"){
		throw Bad_Request();
	}
	bool is_empty = true;
	for(int i=0; i<playlists.size(); i++){
		if(playlists[i].get_username() == commands_in_line[4]){
			if(playlists[i].get_username() == users[enterd_user].get_username()){
				playlists[i].print_all(is_empty);
			}
			else{
				playlists[i].print_publics(is_empty);
			}
		}
	}
	if(is_empty)
		throw Empty();
}

void Utunes::handle_post_playlists_songs(vector<string> commands_in_line){
	if(commands_in_line[0] != "POST" || commands_in_line[1] != "playlists_songs"){
		return;
	}
	if(commands_in_line.size() != 7 || commands_in_line[3] != "playlist_id" 
		|| commands_in_line[5] != "song_id"){
		throw Bad_Request();
	}
	for(int i=0; i<playlists.size(); i++){
		if(playlists[i].get_id() == stoi(commands_in_line[4])){
			if(playlists[i].get_username() != users[enterd_user].get_username()){
				throw Permission_Denied();
			}
			playlists[i].add_song(&songs[stoi(commands_in_line[6]) - 1]);
			cout << "OK" << endl;
		}
	}
}

void Utunes::handle_get_playlists_songs(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "playlists_songs"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "playlist_id"){
		throw Bad_Request();
	}
	bool is_empty = true;
	for(int i=0; i<playlists.size(); i++){
		if(playlists[i].get_id() == stoi(commands_in_line[4])){
			if(playlists[i].get_username() != users[enterd_user].get_username()
				&& playlists[i].get_is_private()){
				throw Permission_Denied();
			}
			playlists[i].print_songs(is_empty);
		}
	}
}

void Utunes::handle_delete_playlists_songs(vector<string> commands_in_line){
	if(commands_in_line[0] != "DELETE" || commands_in_line[1] != "playlists_songs"){
		return;
	}
	if(commands_in_line.size() != 7 || commands_in_line[3] != "playlist_id" 
		|| commands_in_line[5] != "song_id"){
		throw Bad_Request();
	}
	for(int i=0; i<playlists.size(); i++){
		if(playlists[i].get_id() == stoi(commands_in_line[4])){
			if(playlists[i].get_username() != users[enterd_user].get_username()){
				throw Permission_Denied();
			}
			playlists[i].delete_song(stoi(commands_in_line[6]));
			songs[stoi(commands_in_line[6])-1].decrease_playlists();
		}
	}
}

void Utunes::handle_get_users(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "users"){
		return;
	}
	if(users.size() == 1)
		throw Empty();
	vector<string> usernames;
	for(int i=0; i<users.size(); i++){
		if(users[i].get_username() == users[enterd_user].get_username())
			continue;
		usernames.push_back(users[i].get_username());
	}
	usernames = sort_alphabetically(usernames);
	for(int i=0; i<usernames.size(); i++){
		cout << usernames[i] << endl;
	}
}

void Utunes::handle_filters(vector<string> commands_in_line){
	if(commands_in_line[0] != "POST" || commands_in_line[1] != "filters"){
		return;
	}
	if(commands_in_line.size() < 5 || commands_in_line[2] != "?"){
		throw Bad_Request();
	}
	if(commands_in_line[3] == "artist"){
		string artist_name = commands_in_line[4];
		for(int i=5; i<commands_in_line.size(); i++){
			artist_name = artist_name + " " + commands_in_line[i];
		}
		filters["artist"] = artist_name;
	}
	else if(commands_in_line[3] == "min_year")
		filters["year"] = (commands_in_line[4] + " " + commands_in_line[6]);
	else if(commands_in_line[3] == "min_like")
		filters["like"] = (commands_in_line[4] + " " + commands_in_line[6]);
	else
		return;

	Filter* artist_filter = new Artistfilter();
	Filter* year_filter = new Yearfilter();
	Filter* like_filter = new Likefilter();
	filtered_songs = songs;
	if(filters["artist"] != " "){
		filtered_songs = artist_filter->apply_filter(songs, filters["artist"], "");
	}
	if(filters["year"] != " "){
		vector<string> year_datas = split_command_line(filters["year"]);
		filtered_songs = year_filter->apply_filter(filtered_songs
			, year_datas[0], year_datas[1]);
	}
	if(filters["like"] != " "){
		vector<string> like_datas = split_command_line(filters["like"]);
		filtered_songs = like_filter->apply_filter(filtered_songs
			, like_datas[0], like_datas[1]);
	}
	cout << "OK" << endl;
	delete artist_filter;
	delete year_filter;
	delete like_filter;
}

void Utunes::handle_delete_filters(vector<string> commands_in_line){
	if(commands_in_line[0] != "DELETE" || commands_in_line[1] != "filters"){
		return;
	}
	filtered_songs = songs;
	filters["artist"] = " ";
	filters["year"] = " ";
	filters["like"] = " ";
	cout << "OK" << endl;
}

void Utunes::handle_post_comments(vector<string> commands_in_line){
	if(commands_in_line[0] != "POST" || commands_in_line[1] != "comments"){
		return;
	}
	if(commands_in_line.size() != 9 || commands_in_line[3] != "song_id" 
		|| commands_in_line[5] != "time" || commands_in_line[7] != "comment"){
		throw Bad_Request();
	}
	for(int i=0; i<songs.size(); i++){
		if(songs[i].get_id() == stoi(commands_in_line[4])){
			Comment new_comment;
			new_comment.time = stoi(commands_in_line[6]);
			new_comment.username = users[enterd_user].get_username();
			new_comment.comment = commands_in_line[8];
			songs[i].add_comment(new_comment);
			cout << "OK" << endl;
			return;
		}
	}
	throw Not_Found();
}

void Utunes::handle_get_comments(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "comments"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "song_id"){
		throw Bad_Request();
	}
	if(commands_in_line.size() < 5 || commands_in_line[2] != "?"){
		throw Bad_Request();
	}
	for(int i=0; i<songs.size(); i++){
		if(songs[i].get_id() == stoi(commands_in_line[4])){
			songs[i].print_comments(commands_in_line);
			return;
		}
	}
	throw Not_Found();
}

void Utunes::handle_throws(vector<string> commands_in_line){
	if(commands_in_line.size() < 2)
		throw Bad_Request();
	if(commands_in_line[0] != "POST" && commands_in_line[0] != "GET" 
		&& commands_in_line[0] != "DELETE"){
		throw Bad_Request();
	}
	if(commands_in_line[1] != "signup" && commands_in_line[1] != "login" 
		&& commands_in_line[1] != "logout" && commands_in_line[1] != "" 
		&& commands_in_line[1] != "songs" && commands_in_line[1] != "likes" 
		&& commands_in_line[1] != "playlists" && commands_in_line[1] != "playlists_songs" 
		&& commands_in_line[1] != "users" && commands_in_line[1] != "filters" 
		&& commands_in_line[1] != "comments" && commands_in_line[1] != "similar_users"
		&& commands_in_line[1] != "recommended"){
		throw Not_Found();
	}
	if(commands_in_line[1] != "signup" && commands_in_line[1] != "login"){
		if(enterd_user == -1)
			throw Permission_Denied();
	}
}

void Utunes::update_users_and_songs_matrix(){
	users_and_songs_matrix.clear();
	vector<int> likes;
	for(int i=0; i<users.size(); i++){
		likes.clear();
		for(int j=0; j<songs.size(); j++){
			if(users[i].is_liked(&songs[j]))
				likes.push_back(1);
			else
				likes.push_back(0);
		}
		users_and_songs_matrix.push_back(likes);
	}
}

void Utunes::update_similarity_matrix(){
	similarity_matrix.clear();
	vector<double> similarity;
	for(int i=0; i<users.size(); i++){
		vector<Song*> v1 = users[i].get_liked_songs();
		similarity.clear();
		for(int j=0; j<users.size(); j++){

			vector<Song*> v2 = users[j].get_liked_songs();
			double same_num = 0;
			for(int m=0; m<v1.size(); m++){
				for(int n=0; n<v2.size(); n++){
					if(v1[m]->get_id() == v2[n]->get_id()){
						same_num++;
						break;
					}
				}
			}
			similarity.push_back(same_num/songs.size());
		}
		similarity_matrix.push_back(similarity);
	}
}

void Utunes::handle_similar_users(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "similar_users"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "count" 
		|| stoi(commands_in_line[4])<0){
		throw Bad_Request();
	}
	update_users_and_songs_matrix();
	update_similarity_matrix();
	vector<Similarity> similarity_vector;
	for(int i=0; i<users.size(); i++){
		if(i == enterd_user)
			continue;
		Similarity new_similarity;
		new_similarity.username = users[i].get_username();
		new_similarity.similarity = similarity_matrix[enterd_user][i];
		similarity_vector.push_back(new_similarity);
	}
	similarity_vector = sort_by_usern(similarity_vector);
	similarity_vector = sort_by_similarity(similarity_vector);
	for(int i=0; i<similarity_vector.size(); i++){
		if(stoi(commands_in_line[4]) == i)
			break;
		cout << fixed << setprecision(2) << similarity_vector[i].similarity*100;
		cout << "% " << similarity_vector[i].username << endl;
	}
}
double Utunes::calculate_confidence(int song){
	double A = 0;
	for (int i=0; i<users.size(); i++){
		if(i == enterd_user)
			continue;
		A += users_and_songs_matrix[i][song] * similarity_matrix[enterd_user][i];
	}
	return (A / (users.size() - 1));
}
void Utunes::handle_recommended(vector<string> commands_in_line){
	if(commands_in_line[0] != "GET" || commands_in_line[1] != "recommended"){
		return;
	}
	if(commands_in_line.size() != 5 || commands_in_line[3] != "count" 
		|| stoi(commands_in_line[4])<0){
		throw Bad_Request();
	}
	if(users.size() == 1)
		return;
	update_users_and_songs_matrix();
	update_similarity_matrix();
	vector<Recom> recom_vector;
	for(int i=0; i<songs.size(); i++){
		if(users_and_songs_matrix[enterd_user][i] == 1){
			continue;
		}
		Recom new_recom;
		new_recom.song_id = i + 1;
		double confidence_ = calculate_confidence(i);
		new_recom.confidence = confidence_;
		recom_vector.push_back(new_recom);
	}
	recom_vector = sort_by_confidence(recom_vector);
	for(int i=0; i<recom_vector.size(); i++){
		if(stoi(commands_in_line[4]) == i)
			break;
		int song_id = recom_vector[i].song_id;
		cout << song_id << " ";
		cout << fixed << setprecision(2) << recom_vector[i].confidence*100;
		cout << "% " << songs[song_id-1].get_title() << " ";
		cout << songs[song_id-1].get_artist() << " ";
		cout << songs[song_id-1].get_released_year() << endl;
	}
}