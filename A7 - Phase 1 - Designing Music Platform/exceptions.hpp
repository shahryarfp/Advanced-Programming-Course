#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class Bad_Request : public exception{
public:
const char* what() const noexcept{ return "Bad Request\n"; }
};

class Permission_Denied : public exception{
public:
const char* what() const noexcept{ return "Permission Denied\n"; }
};

class Empty : public exception{
public:
const char* what() const noexcept{ return "Empty\n"; }
};

class Not_Found : public exception{
public:
const char* what() const noexcept{ return "Not Found\n"; }
};


#endif