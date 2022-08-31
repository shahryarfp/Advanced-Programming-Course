#include <sstream>
#include <iostream>
#include <vector>
#include "handlers.hpp"

using namespace std;


Response *show_first_page::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  << "<!DOCTYPE html>"<<endl
  << "<html>" << endl
  << " <body style=\"text-align: center;\">" << endl
  << "   <h1>uTunes</h1>" << endl
  << "   <img src=\"/utuneslogo.png\" style=\"width:25%;\">" << endl
  << "   <br />" << endl
  << "   <a href=\"/login\">login</a>" << endl
  << "   <br />" << endl
  << "   <a href=\"/signup\">sign up</a>" << endl
  << "   <br />" << endl
  << " </body>" << endl
  << "</html>" << endl;

  res->setBody(body.str());
  return res;
}
Response *signupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string email = req->getBodyParam("email");
  string password = req->getBodyParam("password");
  vector<string> command;
  command.push_back("Post");command.push_back("signup");
  command.push_back("?");command.push_back("email");
  command.push_back(email);command.push_back("username");
  command.push_back(username);command.push_back("password");
  command.push_back(password);
  try{
    utunes-> handle_signup(command);
    return Response::redirect("/");
  }catch(exception& ex){
    string what = ex.what();
    string s = "/errors?error=" + what;
    return Response::redirect(s);
  }
}

Response *LoginHandler::callback(Request *req) {
  string email = req->getBodyParam("email");
  string password = req->getBodyParam("password");
  vector<string> command;
  command.push_back("Post");command.push_back("login");
  command.push_back("?");command.push_back("email");
  command.push_back(email);command.push_back("password");
  command.push_back(password);
  try{
    utunes-> handle_login(command);
    return Response::redirect("/user_homepage");
  }catch(exception& ex){
    string what = ex.what();
    string s = "/errors?error=" + what;
    return Response::redirect(s);
  }
}

Response *handle_user_homepage::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body = utunes->make_songs_body();
  res->setBody(body.str());
  return res;
}

Response *handle_logout::callback(Request *req) {
  utunes->handle_logout();
  return Response::redirect("/");
}

Response *handle_errors::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  << "<!DOCTYPE html>"<<endl
  << "<html>" << endl
  << " <body style=\"text-align: center;\">" << endl
  << "   <h1>uTunes</h1>" << endl
  << "   <br />" << endl
  << "   <p>error: " << req->getQueryParam("error")<<"</p>"<<endl
  << "   <br />" << endl
  << " </body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

Response *handle_song_info::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body = utunes->make_song_info_body(stoi(req->getQueryParam("id")));
  res->setBody(body.str());
  return res;
}