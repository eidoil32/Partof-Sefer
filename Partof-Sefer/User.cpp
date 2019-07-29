#include <iostream>
using namespace std;

#include "User.h"
#include "Facebook.h"

User::User(const string& name)
{
	this->name = name;
	countMember = 0;
	wall.reserve(BASE_SIZE);
	friendlist.reserve(BASE_SIZE);
}

void User::printAllUsers() const
{
	bool type = !(TYPEID_CHECK(*this, member));

	auto itr 	= friendlist.begin();
	auto itrEnd = friendlist.end();

	if (friendlist.size() == 0)
		cout << name << " doesn't have any friends!\n";
	else
	{
		if (countMember > 0)
		{
			cout << (type ? "Fans:" : "Friends:") << endl;
			for (int i = 1; itr != itrEnd; ++itr,i++)
				if (TYPEID_CHECK(**itr, member))
					cout << i << ". " << (*itr)->getname() << endl;
		}

		if ((friendlist.size() - countMember) > 0 && !type)
		{
				cout << "Loved Fanlists:\n";
				itr = friendlist.begin();
				for (int i = 1; itr != itrEnd; ++itr, i++)
					if (TYPEID_CHECK(**itr, Fanlist))
						cout << i << ". " << (*itr)->getname() << endl;
		}
	}
	cout << endl;
}

User::~User()
{
	int size = wall.size();
	for (int i = 0; i < size; i++)
		delete wall[i];
}

void User::printAllStatus() const
{
	auto itr 	= wall.begin();
	auto itrEnd = wall.end();

	if (wall.size() == 0)
		cout << "User doesn't have any status!\n";
	else
	{
		for (int i = 1; itr != itrEnd; ++itr,i++)
		{
			cout << "\nStatus no." << i;
			(*itr)->printstatus();
		}
	}
	cout << endl;
}

void User::poststatus()
{
	auto itr 	= friendlist.begin();
	auto itrEnd = friendlist.end();

	if (wall.capacity() == wall.size())
		wall.reserve(wall.capacity()*2);

	wall.push_back(newStatus(this->getname()));

	for (; itr != itrEnd; ++itr)
	{
		if (TYPEID_CHECK(**itr, member))
		{
			((member*)(*itr))->addtorecentstatus(wall[wall.size()-1]);
		}
	}

}

const User & User::operator+=(User & newFriend)
{
	if ((this->getname() == newFriend.getname()) && TYPEID_CHECK(*this, newFriend))
	{
		cout << "Command failed! You cannot be friend of yourself!\n";
		return *this;
	}
	if (checkNameAlreadyExist(newFriend.getname(), friendlist, TYPE_MEMBER) == INT_TRUE)
		return *this;

	if (friendlist.capacity() == friendlist.size())
		friendlist.reserve(friendlist.capacity()*2);

	if (TYPEID_CHECK(newFriend, member))
		countMember++;
	friendlist.push_back(&newFriend);
	newFriend += (*this);

	return *this;
}

bool User::operator>(const User& user1)
{
	int size1 = user1.getNumOfFriends(), size2 = friendlist.size();
		return  size1 < size2 ;
}