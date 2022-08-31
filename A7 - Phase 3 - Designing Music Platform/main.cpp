#include <iostream>
#include "song.hpp"
#include "functions.hpp"
#include "utunes.hpp"

#include "handlers.hpp"
#include "my_server.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	vector<Song> songs = read_songs_file(argv);
	vector<Liked_Song> liked_songs = read_liked_songs_file(argv);
	Utunes utunes = Utunes(songs, liked_songs);
  try {
    MyServer server(5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new show_first_page());
    server.get("/utuneslogo.png", new ShowImage("static/utuneslogo.png"));
    server.get("/signup", new ShowPage("static/signup_page.html"));
    server.post("/signup_action", new signupHandler(&utunes));
    server.get("/login", new ShowPage("static/login_page.html"));
    server.post("/login_action", new LoginHandler(&utunes));
    server.get("/user_homepage", new handle_user_homepage(&utunes));
    server.get("/logout", new handle_logout(&utunes));
    server.get("/errors", new handle_errors());
    server.get("/song_info", new handle_song_info(&utunes));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
  return 0;
}