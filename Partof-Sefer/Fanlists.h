#pragma once

#include "User.h"
#include "Members.h"

class Fanlist: public User 
{
	Fanlist(const Fanlist& other);// no need for cpy ctor
public:
	Fanlist(string &name) : User(name) {}
	~Fanlist() {}
};
