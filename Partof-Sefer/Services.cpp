#include <iostream>
using namespace std;

#include "Services.h"

void getFullDate(int &day, int &month, int &year)
{
	day = cinInt();
	cin.ignore();
	month = cinInt();
	cin.ignore();
	year = cinInt();
}

int cinInt()
{
	int choice;
	bool showOnlyOnce = true;
	while (!(cin >> choice)) // cin return false if value isn't correct
	{
		if (showOnlyOnce)
		{
			ERROR_COMMAND("Bad value! Please enter a vaild number.\n")
		}
		showOnlyOnce = false;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

vector<User *> MakeRightArray(vector<User *>arr, bool flag)// newsize-> to be efficient
{
	vector<User *>temparr;

	temparr.reserve(arr.size());

	auto itr = arr.begin(), itrEnd = arr.end();

	for (; itr != itrEnd; ++itr)
	{
		if (TYPEID_CHECK(**itr,member) && !flag)
			temparr.push_back(*itr);

		if (TYPEID_CHECK(**itr,Fanlist) && flag)
			temparr.push_back(*itr);
	}

	return temparr;
}

int checkNameAlreadyExist(string name, vector<User*>arr, bool type)
{
	auto itr = arr.begin(), itrEnd = arr.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getname() == name)
		{
			if (type == TYPE_MEMBER && TYPEID_CHECK(**itr, member))
				return INT_TRUE;
			if (type == TYPE_FANLIST && TYPEID_CHECK(**itr, Fanlist))
				return INT_TRUE;
		}
	}
	return INT_FALSE;
}

void printPictureASCII()
{
	cout << R"(  , ; ,   .-'"""'-.   , ; ,
  \\|/  .'         '.  \|//
   \-;-/   (@)   (@)   \-;-/
   // ;               ; \\
  //__; :.         .; ;__\\
 `-----\'.'-.....-'.'/-----'
        '.'.-.-,_.'.'
          '(  (..-'
            '-')" << endl;
}

void printVideoASCII()
{
	setTextColor(Color::LIGHTMAGENTA);
	cout << R"(       _     _            
      (_)   | |           
__   ___  __| | ___  ___  
\ \ / / |/ _` |/ _ \/ _ \ 
 \ V /| | (_| |  __/ (_) |
  \_/ |_|\__,_|\___|\___/)" << endl;
  	setTextColor(Color::WHITE);
}