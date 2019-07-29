#include <iostream>
using namespace std;

#include "Members.h"

void member::printrecentstatus() const
{
	auto itr = friendsStatus.begin(),	itrEnd = friendsStatus.end();

	if (friendsStatus.size() == 0)
	{
		ERROR_COMMAND(name << "'s friends didn't publish any status\n")
	}
	else
		for (int i = 1; itr!=itrEnd; ++itr, i++)
		{
			cout << "Status no. " << i;
			(*itr)->printstatus();
		}
}

member::member(const string name, const Date &birthdate) :User(name)
{
	this->birthdate = new Date(birthdate);
}

void member::addtorecentstatus(status *status)
{
	if (friendsStatus.size() == RECENT_STATUS_NUM)
		friendsStatus.pop_back(); //remove the oldest ststus

	friendsStatus.push_front(status);
}

//
void member::newfriendtorecentstatus(vector<status*> friendrecent)
{
	list<status*>temp;
	auto friendItr = friendrecent.begin(), friendItrEnd = friendrecent.end();
	auto itr = friendsStatus.begin(), itrEnd = friendsStatus.end();
	int count = 0;

	while ((itr != itrEnd) && (friendItr != friendItrEnd) && count < RECENT_STATUS_NUM)
	{
		if ((*itr)->getDate() < (*friendItr)->getDate())
		{
			temp.push_back(*friendItr);
			++friendItr;
		}
		else
		{
			temp.push_back(*itr);
			++itr;
		}
		count++;
	}

	while ((itr != itrEnd) && count < RECENT_STATUS_NUM)
	{
		temp.push_back(*itr);
		++itr;
	}

	while ((friendItr != friendItrEnd) && count < RECENT_STATUS_NUM)
	{
		temp.push_back(*friendItr);
		++friendItr;
	}

	friendsStatus = temp;
}