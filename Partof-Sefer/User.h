#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class status;

class User 
{
protected:
    string name;
    vector<status*> wall;
    vector<User*> friendlist; //includes fanlists and friends
	int countMember;
	User(const string &name);
public:
	User(const User &base) : name(base.getname()) { countMember = 0; }
	virtual ~User();
    void poststatus();
	vector<User*>&		getFriendlist()		{ return friendlist; }
	vector<status*>&	getstatusarray()	{ return wall; }
    string getname()				const	{ return name; }
    void printAllStatus()			const;
	int getNumOfFriends()			const	{ return friendlist.size(); }
    void printAllUsers()			const;
	int getCountMember()			const	{ return countMember; }
	void plusCountMember()					{ countMember++; }
	const User& operator+=(User &newFriend);
	bool operator>(const User & user1);
};