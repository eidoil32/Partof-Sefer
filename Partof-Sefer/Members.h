#pragma once

#include "User.h"
#include "Date.h"
#include "Status.h"
#include "Services.h"
#include "Fanlists.h"
#include "Facebook.h"
#include <list>

const int NOCHANGE = -1, RECENT_STATUS_NUM = 10;

status* newStatus(const string posterName);

class member : public User
{
	Date *birthdate;
	list<status*>friendsStatus;
	member(const member&member);// no need for cpy ctor
public:
	member(const string name,const Date& birthdate);
	~member()											{ delete birthdate; }
	void printDate()							const	{ birthdate->showdate(); }  
	Date *getBirthdate()						const	{ return birthdate; }
	void printrecentstatus()					const;
	list<status*>&getRecenetStatusArray()				{ return friendsStatus; }
	void addtorecentstatus(status *status);
	void newfriendtorecentstatus(vector<status*> friendrecent);
};