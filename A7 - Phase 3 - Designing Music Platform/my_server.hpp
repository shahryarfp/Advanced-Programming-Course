#ifndef MY_SERVER
#define MY_SERVER

#include "server/server.hpp"

class MyServer:public Server {
public:
  MyServer(int port = 5000);
};

#endif